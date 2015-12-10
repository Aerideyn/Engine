#include "Shader.h"
#include "Texture2D.h"
#include "ShaderLoader.h"
#include <GL\glew.h>
#include <iostream>
#include "Window.h"

void Render::Shader::AssociateNamesWithLocations()
{
	// get number of uniforms.
	int uniformCount = 0;
	glGetProgramiv(ProgramID, GL_ACTIVE_UNIFORMS, &uniformCount);

	// 
	int NameLength = -1;

	// for each sampler in the uniform list associate it with a texture input.
	int TextureUnit = 0;
	for (int i = 0; i < uniformCount; i++)
	{
		GLenum type = GL_ZERO;
		char name[100];
		int uniformSize = -1;
		int nameLength = -1;
		glGetActiveUniform(ProgramID, GLuint(i), sizeof(name)-1, &nameLength, &uniformSize, &type, name);
		if (type == GL_SAMPLER_2D) SamplerLocationToTextureUnit[i] = TextureUnit++;
		
		NameToLocationMap[name] = i;
	}
}

Render::Shader::Shader()
{
	ProgramID = -1;
	programIsValid = false;
}

Render::Shader::Shader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath)
{
	ProgramID = detail::ShaderLoader::LoadShader(VertexShaderFilePath, FragmentShaderFilePath);
	programIsValid = static_cast<int>(ProgramID) != -1;
	AssociateNamesWithLocations();
}

Render::Shader::Shader(const unsigned int VertexShader, const unsigned int FragmentShader)
{
	ProgramID = detail::ShaderLoader::LoadShader(VertexShader, FragmentShader);
	programIsValid = static_cast<int>(programIsValid) != -1;
	AssociateNamesWithLocations();
}

Render::Shader::~Shader()
{
	//glUseProgram(0);
	//glDeleteProgram(ProgramID);
}

void Render::Shader::UseProgram()
{
	glUseProgram(ProgramID);
}

void Render::Shader::ApplyMatrix(const std::string UniformName, const glm::mat4x4& Matrix)
{
	if (NameToLocationMap.find(UniformName) == NameToLocationMap.end())
	{
		if (logmissinguniforms) std::cout << "Could not find uniform " << UniformName << " was the uniform optimised away?" << std::endl;
		return;
	}
	else
	{
		glUniformMatrix4fv(NameToLocationMap[UniformName], 1, GL_FALSE, &Matrix[0][0]);
	}
}

void Render::Shader::ApplyVector(std::string Name, const glm::vec3& Vector)
{
	if (NameToLocationMap.find(Name) == NameToLocationMap.end())
	{
		if (logmissinguniforms) std::cout << "Could not find uniform " << Name << " was the uniform optimised away?" << std::endl;
		return;
	}
	else
	{
		glUniform3f(NameToLocationMap[Name], Vector.x, Vector.y, Vector.z);
	}
}

void Render::Shader::ApplyFloat(std::string Name, float x)
{
	if (NameToLocationMap.find(Name) == NameToLocationMap.end())
	{
		if (logmissinguniforms) std::cout << "Could not find uniform " << Name << " was the uniform optimised away?" << std::endl;
		return;
	}
	else
	{
		glUniform1f(NameToLocationMap[Name], x);
	}
}

void Render::Shader::ApplyTexture(std::string SamplerName, const Texture2D& Texture)
{
	GLuint handle = -1;

	// check that the texture is actually valid..
	if (Texture.handle != nullptr)
	{
		handle = Texture.handle->GetHandle();
		if (handle != static_cast<GLuint>(-1))
		{
			//first look up which texture unit the sampler was assigned to at construction.
			auto iter = NameToLocationMap.find(SamplerName);
			if (iter != NameToLocationMap.end())
			{
				int SamplerLocation = iter->second;
				int TextureUnit = SamplerLocationToTextureUnit[SamplerLocation];

				// assign and bind texture to the texture unit.
				glActiveTexture(GL_TEXTURE0 + TextureUnit);
				glBindTexture(GL_TEXTURE_2D, handle);

				// bind the sampler to the same texture unit.
				glUniform1i(SamplerLocation, TextureUnit);
				return;
			}
		}
	}
	if (handle != static_cast<GLuint>(-1))
		std::cout << "Attempt to bind texture failed; Could not find sampler " << SamplerName << ". Was it optimised away?" << std::endl;
	else
		std::cout << "Attempt to bind texture failed; Invalid handle." << std::endl;
}

void Render::Shader::DrawIndexedElements(int indexCount)
{
	int wireframemode = (enableWireframe) ? GL_LINE : GL_FILL;

	if (enableBackfaceCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (enableDepthTesting)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	glPolygonMode(GL_FRONT_AND_BACK, wireframemode);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, nullptr);
}

void Render::Shader::DrawNonIndexedElements(int VertexCount, bool Lines)
{
	int wireframemode = (enableWireframe) ? GL_LINE : GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, wireframemode);

	if (enableBackfaceCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);

	if (enableDepthTesting)
		glEnable(GL_DEPTH_TEST);
	else
		glDisable(GL_DEPTH_TEST);

	if (Lines)
	{
		glDrawArrays(GL_LINES, 0, VertexCount);
	}
	else
		glDrawArrays(GL_TRIANGLES, 0, VertexCount);
}