#pragma once
#include <glm\glm.hpp>
#include <string>
#include <vector>
#include <map>
namespace Render
{
	class Texture2D;
	class Shader
	{
	private:
		bool programIsValid;
		unsigned int ProgramID;
		std::map<int, int> SamplerLocationToTextureUnit;
		std::map<std::string, int> NameToLocationMap;
		void AssociateNamesWithLocations();

		bool logmissinguniforms = false;
		bool enableWireframe = false;
		bool enableBackfaceCulling = true;
		bool enableDepthTesting = true;

	public:
		Shader();
		Shader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath);
		Shader(const unsigned int VertexShader, const unsigned int FragmentShader);
		void LogMissingUniforms(bool Enabled) { logmissinguniforms = Enabled; };

		void UseProgram();
		void ApplyMatrix(const std::string Name, const glm::mat4x4&);
		void ApplyTexture(std::string SamplerName, const Texture2D& Texture);
		void ApplyVector(std::string Name, const glm::vec3& Vector);
		void ApplyFloat(std::string Name, float x);

		void DrawIndexedElements(int IndexCount);
		void DrawNonIndexedElements(int VertexCount, bool Lines);
		void SetWireFrameMode(bool enabled) { enableWireframe = enabled; };
		void SetDepthTestMode(bool enabled) { enableDepthTesting = enabled; };
		void SetBackfaceCullingmode(bool enabled) { enableBackfaceCulling = enabled; };
		~Shader();
	};
}