#include "ShaderLoader.h"
#include "Window.h"
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <GL/glew.h>

// declarations.
std::string detail::ShaderLoader::rootFilePath = "";
std::map<const char*, unsigned int> detail::ShaderLoader::FragmentShaderIDMap = std::map<const char*, unsigned int>();
std::map<const char*, unsigned int> detail::ShaderLoader::VertexShaderIDMap = std::map<const char*, unsigned int>();
std::map<std::pair<unsigned int, unsigned int>, unsigned int> detail::ShaderLoader::ShaderIDMap = std::map<std::pair<unsigned int, unsigned int>, unsigned int>();

GLuint CreateFragmentShader(const char*);
GLuint CreateVertexShader(const char*);
GLuint CreateFragmentShaderFromCode(const char*);
GLuint CreateVertexShaderFromCode(const char*);

GLuint LinkShaders(GLuint VertexShaderID, GLuint FragmentShaderID);


unsigned int detail::ShaderLoader::LoadFragmentShader(const char* Key, bool KeyIsCode)
{
	auto iter = FragmentShaderIDMap.find(Key);
	if (iter != FragmentShaderIDMap.end()) return iter->second;

	// else load parse and compile fragment shader.
	GLuint fragmentshader;
	if (KeyIsCode){
		fragmentshader = CreateFragmentShaderFromCode(Key);
	}
	else{
		fragmentshader = CreateFragmentShader(Key);
	}
	FragmentShaderIDMap[Key] = fragmentshader;
	return fragmentshader;
}

unsigned int detail::ShaderLoader::LoadVertexShader(const char* Key, bool KeyIsCode)
{
	auto iter = VertexShaderIDMap.find(Key);
	if (iter != VertexShaderIDMap.end()) return iter->second;

	// else load parse and compile vertex shader.
	GLuint vertexshader;
	if (KeyIsCode){
		vertexshader = CreateVertexShaderFromCode(Key);
	}
	else{
		vertexshader = CreateVertexShader(Key);
	}
	
	VertexShaderIDMap[Key] = vertexshader;
	return vertexshader;
}

unsigned int detail::ShaderLoader::LoadShaderUsingCode(const char* VertexShaderCode, const char* FragmentShaderCode)
{
	// load parse and compile fragment and vertex shaders if they do not exist already.
	GLuint vertexShader = LoadVertexShader(VertexShaderCode, true);
	GLuint fragmentShader = LoadFragmentShader(FragmentShaderCode, true);

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

unsigned int detail::ShaderLoader::LoadShader(const char* VertexShader, const char* FragmentShader)
{
	// load parse and compile fragment and vertex shaders if they do not exist already.
	GLuint vertexShader = LoadVertexShader(VertexShader, false);
	GLuint fragmentShader = LoadFragmentShader(FragmentShader, false);

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

unsigned int detail::ShaderLoader::LoadShader(unsigned int VertexShader, unsigned int FragmentShader)
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

GLuint CreateVertexShader(const char * vertex_file_path)
{
	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line)) VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Was the correct file path used? !\n", vertex_file_path);
		getchar();
		return -1;
	}

	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		if (Result == 0)
		{
			glDeleteShader(VertexShaderID);
			return -1;
		}
	}
	return VertexShaderID;
}

GLuint CreateVertexShaderFromCode(const char* VertexShaderCode)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling vertex shader from code");
	char const * VertexSourcePointer = VertexShaderCode;
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
		if (Result == 0)
		{
			glDeleteShader(VertexShaderID);
			return -1;
		}
	}
	return VertexShaderID;
}

GLuint CreateFragmentShader(const char * fragment_file_path)
{
	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Was the correct file path used? !\n", fragment_file_path);
		getchar();
		return -1;
	}

	// Create the shaders
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
		if (Result == 0)
		{
			glDeleteShader(FragmentShaderID);
			return -1;
		}
	}
	return FragmentShaderID;
}

GLuint CreateFragmentShaderFromCode(const char* FragmentShaderCode)
{
	// Create the shaders
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Fragment Shader
	printf("Compiling fragment shader from code");
	char const* FragmentSourcePointer = FragmentShaderCode;
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
		if (Result == 0)
		{
			glDeleteShader(FragmentShaderID);
			return -1;
		}
	}
	return FragmentShaderID;
}

GLuint LinkShaders(GLuint VertexShaderID, GLuint FragmentShaderID)
{
	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0){
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}
