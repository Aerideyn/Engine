#pragma once
#include <glm\glm.hpp>

class Shader
{
private:
	bool programIsValid;
	unsigned int ProgramID;
public:

	bool WireFrameMode = false;
	bool EnableBackfaceCulling = true;

	Shader();
	Shader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath);
	Shader(const unsigned int VertexShader, const unsigned int FragmentShader);

	void UseProgram();
	unsigned int GetUniformLocation(const char* UniformName);
	void ApplyUniform(const unsigned int Location , const glm::mat4x4& Matrix);
	void BindTexture(const unsigned int Texture, const unsigned int Sampler , const int TextureIndex);

	void DrawElements(int IndexCount);

	~Shader();
};

