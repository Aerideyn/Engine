#include "Texture2D.h"
#include "TextureLoader.h"
#include "GL\glew.h"
#include "Window.h"
#include <iostream>

// ========= Handle Wrapper ===========\\

// The handle is an object, and will be accessed through a shared pointer.
// Reference counted handles are required to support copying of textures without messy ownership issues.

Render::Texture2D::TextureHandle::TextureHandle(GLuint Handle)
{
	glHandle = Handle;
}

Render::Texture2D::TextureHandle::~TextureHandle()
{
	glDeleteTextures(1, &glHandle);
}

GLuint Render::Texture2D::TextureHandle::GetHandle()
{
	return glHandle;
}

// ======== Texture2D =================\\

int TypeToGLFormat[]
{
	GL_RED,	// single
	GL_RG, // vector2
	GL_RGBA, // vector4
	GL_RGBA // color
};

int TypeToGLType[]
{
	GL_FLOAT, // single
	GL_FLOAT, // vector2
	GL_FLOAT, // vector3
	GL_UNSIGNED_BYTE  // color
};

Render::Texture2D::Texture2D(std::string FilePath, bool GenerateNewTexture)
{
	DataIsCached = true;
	isEmpty = false;
	filepath = FilePath;

	if (GenerateNewTexture)
	{
		detail::PixelBuffer& buffer = detail::TextureLoader::LoadPixelBufferFromFile(FilePath);
		GLuint newTexture;
		glGenTextures(1, &newTexture);
		glBindTexture(GL_TEXTURE_2D, newTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, buffer.width, buffer.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &buffer.data[0]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
		handle = std::shared_ptr<TextureHandle>(new TextureHandle(newTexture));
		mipmappingEnabled = true;
	}
	else
	{
		Texture2D& tex = detail::TextureLoader::LoadTextureFromFile(FilePath);
		handle = tex.handle;
		mipmappingEnabled = tex.mipmappingEnabled;
	}
}

Render::Texture2D::Texture2D(int Width, int Height, FormatType Type, void * Data, bool GenerateMipmaps)
{
	GLuint newTexture;
	DataIsCached = false;
	isEmpty = false;
	glGenTextures(1, &newTexture);
	glBindTexture(GL_TEXTURE_2D, newTexture);	
	glTexImage2D(GL_TEXTURE_2D, 0, TypeToGLFormat[static_cast<int>(Type)], Width, Height, 0, TypeToGLFormat[static_cast<int>(Type)], TypeToGLType[static_cast<int>(Type)], Data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	if (GenerateMipmaps)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	handle = std::shared_ptr<TextureHandle>(new TextureHandle(newTexture));
	mipmappingEnabled = GenerateMipmaps;
}

Render::Texture2D::Texture2D()
{
	isEmpty = true;
}

Render::Texture2D::~Texture2D()
{
	Release();
}

template <typename T>
std::vector<T> Render::Texture2D::GetData(Texture2D::FormatType type)
{
	std::vector<T> returnData = std::vector<T>();
	if (DataIsCached)
	{
		detail::PixelBuffer pb = detail::TextureLoader::LoadPixelBufferFromFile(filepath);
		for (auto iter = pb.data.begin(); iter != pb.data.end(); iter++) returnData.push_back(static_cast<T>(*iter));		
		return returnData;
	}
	else
	{
		GLint Width, Height;
		glBindTexture(GL_TEXTURE_2D, handle->GetHandle());
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &Width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &Height);

		switch (type)
		{
		case Texture2D::FormatType::Single:
		{
											  float* texdata = new float[Width * Height];
											  glGetTexImage(GL_TEXTURE_2D, 0, GL_RED, GL_FLOAT, texdata);
											  for (int i = 0; i < Width * Height; i++) returnData.push_back(static_cast<T>(texdata[i]));
											  delete[] texdata;
											  return returnData;
		}
		case Texture2D::FormatType::Vector2:
		{
											   float* texdata = new float[Width * Height * 2];
											   glGetTexImage(GL_TEXTURE_2D, 0, GL_RG, GL_FLOAT, texdata);
											   for (int i = 0; i < Width * Height; i++) returnData.push_back(static_cast<T>(texdata[i]));
											   delete[] texdata;
											   return returnData;
		}
		case Texture2D::FormatType::Vector4:
		{								    
											   float* texdata = new float[Width * Height * 4];
											   glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_FLOAT, texdata);
											   for (int i = 0; i < Width * Height; i++) returnData.push_back(static_cast<T>(texdata[i]));
											   delete[] texdata;
											   return returnData;
		}
		case Texture2D::FormatType::Color:
		{
											 unsigned char* texdata = new unsigned char[Width * Height * 4];
											 glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, texdata);
											 for (int i = 0; i < Width * Height; i++) returnData.push_back(static_cast<T>(texdata[i]));
											 delete[] texdata;
											 return returnData;
		}
		default:
			return returnData;
		}
	}
}
template std::vector<float> Render::Texture2D::GetData(Texture2D::FormatType type);
template std::vector<unsigned char> Render::Texture2D::GetData(Texture2D::FormatType type);

void Render::Texture2D::SetWrapModeX(Texture2D::WrapMode mode)
{
	glBindTexture(GL_TEXTURE_2D, handle->GetHandle());
	switch (mode)
	{
	case Texture2D::WrapMode::ClampToEdge:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);	
		break;
	case Texture2D::WrapMode::ClampToBorder:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
		break;
	case Texture2D::WrapMode::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		break;
	case Texture2D::WrapMode::Mirror:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);	
		break;
	default:
		break;
	}
}

void Render::Texture2D::SetWrapModeY(Texture2D::WrapMode mode)
{
	switch (mode)
	{
	case Texture2D::WrapMode::ClampToEdge:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		break;
	case Texture2D::WrapMode::ClampToBorder:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
		break;
	case Texture2D::WrapMode::Repeat:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		break;
	case Texture2D::WrapMode::Mirror:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
		break;
	default:
		break;
	}
}

void Render::Texture2D::SetFilterMode(Texture2D::FilterMode mode)
{
	switch (mode)
	{
	case Texture2D::FilterMode::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		break;
	case Texture2D::FilterMode::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		break;
	default:
		break;
	}
	
}

void Render::Texture2D::SetMipmapFilterMode(Texture2D::FilterMode mode)
{
	switch (mode)
	{
	case Texture2D::FilterMode::Nearest:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		break;
	case Texture2D::FilterMode::Linear:
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		break;
	default:
		break;
	}
}

void Render::Texture2D::Release()
{
	handle = nullptr;
}