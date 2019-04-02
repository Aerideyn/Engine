#include "Shader.h"
#include "Game.h"
#include "ContentService.h"
#include <GL\glew.h>

#include <iostream>

Shader::Shader()
{
	ProgramID = -1;
	programIsValid = false;
}

Shader::Shader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath)
{
	ProgramID = Game::GetContentService().LoadShader(VertexShaderFilePath, FragmentShaderFilePath);
	programIsValid = static_cast<int>(programIsValid) != -1;
}

Shader::Shader(const unsigned int VertexShader, const unsigned int FragmentShader)
{
	ProgramID = ProgramID = Game::GetContentService().LoadShader(VertexShader, FragmentShader);
	programIsValid = static_cast<int>(programIsValid) != -1;
}

Shader::~Shader()
{

}

void Shader::UseProgram()
{
	glUseProgram(ProgramID);
}

unsigned int Shader::GetUniformLocation(const char* UniformName)
{
	unsigned int Location = glGetUniformLocation(ProgramID, UniformName);
	if (Location == -1)
	{
		std::cout << "Could not find uniform " << UniformName << " was the uniform optimised away?" << std::endl;
	}
	return Location;
}

void Shader::ApplyUniform(const unsigned int Location, const glm::mat4x4& Matrix)
{
	glUniformMatrix4fv(Location, 1, GL_FALSE, &Matrix[0][0]);
}

void Shader::BindTexture(const unsigned int Texture, const unsigned int Sampler , const int TextureIndex)
{
	if (Texture != 4294967295 && Sampler != 4294967295)
	{
		glActiveTexture(GL_TEXTURE0 + TextureIndex);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glUniform1i(Sampler, TextureIndex);
	}
	else
	{

	}
}

void Shader::DrawElements(int indexCount)
{
	int wireframemode = (WireFrameMode) ? GL_LINE : GL_FILL;
	
	if (EnableBackfaceCulling)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);


	glPolygonMode(GL_FRONT_AND_BACK, wireframemode);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, nullptr);
}