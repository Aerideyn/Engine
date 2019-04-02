#include "ContentService.h"
#include <GL\glew.h>
#include "ShaderLoader.h"
#include <SFML\Graphics\Image.hpp>

#include <iostream>

ContentService::ContentService()
{
	MissingTextureID = LoadGLTexture("Textures/MissingTex.jpg");
}

ContentService::~ContentService()
{

}

GLuint ContentService::LoadFragmentShader(const char* FilePath)
{
	auto iter = FragmentShaderIDMap.find(FilePath);
	if (iter != FragmentShaderIDMap.end()) return iter->second;

	// else load parse and compile fragment shader.
	GLuint fragmentshader = CreateFragmentShader(FilePath);
	FragmentShaderIDMap[FilePath] = fragmentshader;
	return fragmentshader;
}

GLuint ContentService::LoadVertexShader(const char* FilePath)
{
	auto iter = VertexShaderIDMap.find(FilePath);
	if (iter != VertexShaderIDMap.end()) return iter->second;

	// else load parse and compile vertex shader.
	GLuint vertexshader = CreateVertexShader(FilePath);
	VertexShaderIDMap[FilePath] = vertexshader;
	return vertexshader;
}

GLuint ContentService::LoadShader(const char* VertexShader, const char* FragmentShader)
{

	// load parse and compile fragment and vertex shaders if they do not exist already.
	GLuint vertexShader = LoadVertexShader(VertexShader);
	GLuint fragmentShader = LoadFragmentShader(FragmentShader);

	// if the shaders are corrupt indicate this by returning an error code of -1;
	if (vertexShader == -1 || fragmentShader == -1) 
		return -1;

	// has this pair already been linked to form a shader? if so return that.
	auto iter = ShaderIDMap.find(std::make_pair(vertexShader, fragmentShader));
	if (iter != ShaderIDMap.end()) return iter->second;

	// otherwise link shaders and return.
	GLuint shader = LinkShaders(vertexShader, fragmentShader);
	ShaderIDMap[std::make_pair(vertexShader, fragmentShader)] = shader;
	return shader;
}

GLuint ContentService::LoadShader(const GLuint VertexShader, const GLuint FragmentShader)
{
	// if the shaders are corrupt indicate this by returning an error code of -1;
	if (VertexShader == -1 || FragmentShader == -1) 
		return -1;

	// has this pair already been linked to form a shader? if so return that.
	auto iter = ShaderIDMap.find(std::make_pair(VertexShader, FragmentShader));
	if (iter != ShaderIDMap.end()) return iter->second;

	// otherwise link shaders and return.
	GLuint shader = LinkShaders(VertexShader, FragmentShader);
	ShaderIDMap[std::make_pair(VertexShader, FragmentShader)] = shader;
	return shader;
}

GLuint ContentService::LoadGLTexture(const char* filepath)
{
	// check if image has already been loaded - return it if it has.
	auto iter = TextureIDMap.find(filepath);
	if (iter != TextureIDMap.end())
	{
		return iter->second;
	}
	//otherwise load the specified image.
	GLuint new_texture;
	sf::Image img_data;

	if (!img_data.loadFromFile(filepath))
	{
		std::cout << "Could not load texture " << filepath << std::endl;
		return MissingTextureID;
	}
	
	//convert image to texture.
	glGenTextures(1, &new_texture);

	// bind new texture so it may be refered to.
	glBindTexture(GL_TEXTURE_2D, new_texture);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_data.getSize().x, img_data.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());

	//set parameters.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	if (new_texture < 0)
	{
		std::cout << "Could not load texture " << filepath << std::endl;
		return MissingTextureID;
	}
	TextureIDMap[filepath] = new_texture;
	return new_texture;
}
