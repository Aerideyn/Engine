#pragma once
#include <string>
#include <map>

typedef unsigned int GLuint;

class ContentService
{
	friend class Game;
private:
	ContentService();

	GLuint MissingTextureID;

	std::map<const char*, GLuint> TextureIDMap;
	std::map<const char*, GLuint> FragmentShaderIDMap;
	std::map<const char*, GLuint> VertexShaderIDMap;
	std::map<std::pair<GLuint, GLuint>, GLuint> ShaderIDMap;
public:
	GLuint LoadGLTexture(const char* filePath);
	GLuint LoadFragmentShader(const char* FilePath);
	GLuint LoadVertexShader(const char* FilePath);
	GLuint LoadShader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath);
	GLuint LoadShader(const GLuint VertexShader, const GLuint FragmentShader);
	~ContentService();
};
