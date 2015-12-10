#include "Window.h"
#include "RenderTarget.h"
#include "GL\glew.h"
#include "Texture2D.h"

#include <iostream>

int typeToGLFormat[]
{
	GL_R32F,	// single
	GL_RG32F, // vector2
	GL_RGBA32F, // vector4
	GL_RGBA // color
};

int typeToGLPixelFormat[]
{
	GL_RED,	// single
	GL_RG, // vector2
	GL_RGBA, // vector4
	GL_RGBA // color
};

int typeToGLType[]
{
	GL_FLOAT, // single
	GL_FLOAT, // vector2
	GL_FLOAT, // vector3
	GL_UNSIGNED_BYTE  // color
};

//======== FBOHandle ============\\

Render::RenderTarget::FBOHandle::FBOHandle(GLuint Handle)
{
	glHandle = Handle;
}

Render::RenderTarget::FBOHandle::~FBOHandle()
{
	glDeleteFramebuffers(1, &glHandle);
}

GLuint Render::RenderTarget::FBOHandle::GetHandle()
{
	return glHandle;
}

//======== PBOHandle ============\\

Render::RenderTarget::TextureDownloader::PBOHandle::PBOHandle(GLuint Handle)
{
	glHandle = Handle;
}

Render::RenderTarget::TextureDownloader::PBOHandle::~PBOHandle()
{
	glDeleteBuffers(1, &glHandle);
}

GLuint Render::RenderTarget::TextureDownloader::PBOHandle::GetHandle()
{
	return glHandle;
}

// ============ Texture Downloader =========== \\

Render::RenderTarget::TextureDownloader::TextureDownloader(std::shared_ptr<FBOHandle> Handle, FormatType type, int Height, int Width) : fboHandle(Handle), width(Width), height(Height)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fboHandle->GetHandle());
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	GLuint pbo = -1;
	glGenBuffers(1, &pbo);
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pbo);
	switch (type)
	{
	case Render::Texture2D::FormatType::Single:
		glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 4, 0, GL_STREAM_READ);
		break;
	case Render::Texture2D::FormatType::Vector2:
		glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 8, 0, GL_STREAM_READ);
		break;
	case Render::Texture2D::FormatType::Vector4:
		glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 16, 0, GL_STREAM_READ);
		break;
	case Render::Texture2D::FormatType::Color:
		glBufferData(GL_PIXEL_PACK_BUFFER, width * height * 4, 0, GL_STREAM_READ);
		break;
	default:
		break;
	}
	glReadPixels(0, 0, width, height, typeToGLPixelFormat[static_cast<int>(type)], typeToGLType[static_cast<int>(type)], 0);
	fence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);
	pboHandle = std::shared_ptr<PBOHandle>(new PBOHandle(pbo));
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Render::RenderTarget::TextureDownloader::~TextureDownloader(){	}

bool Render::RenderTarget::TextureDownloader::IsDownloadComplete()
{
	GLenum e = glClientWaitSync((GLsync)fence, GL_SYNC_FLUSH_COMMANDS_BIT, 0);

	GLenum er = glGetError();
	if (er != 0)
		int x = 0;

	if (GL_ALREADY_SIGNALED == e || e == GL_CONDITION_SATISFIED)
	{
		glDeleteSync((GLsync)fence);
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T>
std::vector<T> Render::RenderTarget::TextureDownloader::GetData(Render::Texture2D::FormatType type)
{
	std::vector<T> returnData = std::vector<T>();
	glBindBuffer(GL_PIXEL_PACK_BUFFER, pboHandle->GetHandle());
	float* texdata = (float*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
	if (texdata != nullptr)
	{
		glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		for (int i = 0; i < width * height; i++) 
			returnData.push_back(static_cast<float>(texdata[i]));
	}
	// back to conventional pixel operation
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	return returnData;
}
template std::vector<float> Render::RenderTarget::TextureDownloader::GetData(Texture2D::FormatType type);
template std::vector<unsigned char> Render::RenderTarget::TextureDownloader::GetData(Texture2D::FormatType type);

void Render::RenderTarget::TextureDownloader::Release()
{
	pboHandle = nullptr;
	fboHandle = nullptr;
}

// ============= RenderTarget ============== \\

Render::RenderTarget::RenderTarget(int Height, int Width, Texture2D::FormatType Type)
{
	height = Height;
	width = Width;
	type = Type;
	isEmpty = false;
	newTargetRequired = true;
}

void Render::RenderTarget::BindRenderTarget()
{
	if (newTargetRequired)
	{
		//create new FBO and texture.
		GLuint fbo = -1;
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		FrameBuffer = std::shared_ptr<FBOHandle>(new FBOHandle(fbo));

		// Create the texture we're going to render to
		GLuint Texture = -1;
		glGenTextures(1, &Texture);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glTexImage2D(GL_TEXTURE_2D, 0, typeToGLFormat[static_cast<int>(type)], width, height, 0, typeToGLPixelFormat[static_cast<int>(type)], typeToGLType[static_cast<int>(type)], 0);
		handle = std::shared_ptr<TextureHandle>(new TextureHandle(Texture));

		// Poor filtering. Needed !
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	glBindTexture(GL_TEXTURE_2D, handle->GetHandle());
	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, handle->GetHandle(), 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers

	glViewport(0, 0, height, width); // resize viewport to fit texture.
}

void Render::RenderTarget::DisableRenderTarget()
{
	// Render to the screen
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// return to previous size.
	int x = Window::GetActiveWindow().GetWidthX();
	int y = Window::GetActiveWindow().GetWidthY();
	glViewport(0, 0, x, y);
}

void Render::RenderTarget::Release()
{
	handle = nullptr;
	FrameBuffer = nullptr;
}

Render::RenderTarget::TextureDownloader Render::RenderTarget::GetTextureDownloader()
{
	newTargetRequired = true;
	return Render::RenderTarget::TextureDownloader(FrameBuffer,type,height,width);
}