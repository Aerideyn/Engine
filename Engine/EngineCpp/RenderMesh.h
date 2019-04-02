#pragma once
#include <glm\glm.hpp>
#include <vector>
#include <map>

namespace MeshDrawMode
{
	enum MeshDrawMode
	{
		Triangles,
		Lines,
	};
}

class RenderMesh
{
private: 
	std::map<unsigned int , unsigned int> TextureSamplerMapper;

	MeshDrawMode::MeshDrawMode mode;

	glm::mat4x4 ModelMatrix;
	glm::mat4x4 WorldMatrix;
	glm::mat4x4 ViewProjectionMatrix;

	bool ModelMatrixValid = false;
	bool WorldMatrixValid = false;
	bool ViewProjectionMatrixValid = false;

	unsigned int ModelMatrixLocation = -1;
	unsigned int WorldMatrixLocation = -1;
	unsigned int ViewProjectionMatrixLocation = -1;

	unsigned int indexBuffer = -1;
	bool IndexBufferUsed = false;
	size_t indiceTypeSize = 0;
	size_t indexCount = 0;
	int indiceType = 0;
	
	unsigned int VertexBuffer = -1;
	bool VertexBufferUsed = false;
	size_t vertexCount = 0;

	unsigned int NormalBuffer = -1;
	bool NormalBufferUsed = false;

	unsigned int UVbuffer = -1;
	bool UVBufferUsed = false;

	unsigned int programID;

	bool WireFrameMode = false;
	bool BackfaceCullingEnabled = true;

public:
	void SetVerticies(const std::vector<glm::vec3>& vertices);
	void SetUVCoordinates(const std::vector<glm::vec2>& uvs);
	void SetNormals(const std::vector<glm::vec3>& normals);

	void SetIndicies(const std::vector<unsigned short>& indicies);
	void SetIndicies(const std::vector<unsigned int>& indicies);
	void SetIndicies(const std::vector<int>& indicies);

	void SetModelMatrix(const glm::mat4x4& modelMatrix);
	void SetWorldMatrix(const glm::mat4x4& worldMatrix);
	void SetWorldMatrix(const glm::vec3& translation);
	void SetWorldMatrix(const glm::dvec3& translation);
	void SetViewProjectionMatrix(glm::mat4x4 viewProjectionMatrix);

	void AddTexture(const char* TextureName, const char* SamplerName);
	void AddTexture(const unsigned int TextureID, const char* SamplerName);

	inline void SetWireFrameMode(bool IsEnabled){ WireFrameMode = IsEnabled; };
	inline void EnableBackfaceCulling(bool enabled){ BackfaceCullingEnabled = enabled; };

	inline void SetDrawMode(MeshDrawMode::MeshDrawMode Mode){ mode = Mode; };

	void Draw();

	RenderMesh(unsigned int ShaderID);
	RenderMesh(const char* VertexShader, const char* FragmentShader);

	~RenderMesh();
};

