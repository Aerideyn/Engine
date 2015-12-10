#include "SphereRenderer.h"
#include "Shader.h"
#include "Texture2D.h"
#include "AttributeBuffers.h"
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

float const pi = 3.1415926535897932384626433832795f;
float const piOn2 = 1.5707963267948966192313216916398f;

CommonObjects::RenderablePrimitives::SphereRenderer::SphereRenderer(glm::dvec3 Centre, double Radius, int Rows, int Columns)
{
	objectMatrix = glm::mat4x4();
	position = Centre;
	radius = Radius;
	CreateVertexBuffer(Rows, Columns);
	CreateIndexBuffer(Rows, Columns);
	shader = new Render::Shader("Shaders/Basic.vertexshader", "Shaders/Basic.fragmentshader");
	texture = new Render::Texture2D("Textures/MissingTex.png", true);
}

CommonObjects::RenderablePrimitives::SphereRenderer::SphereRenderer()
{

	position = glm::dvec3();
	radius = 1.0;
	CreateVertexBuffer(3, 3);
	CreateIndexBuffer(3, 3);
	shader = new Render::Shader("Shaders/Basic.vertexshader", "Shaders/Basict.fragmentshader");
	texture = new Render::Texture2D("Textures/MissingTex.png", true);
}

CommonObjects::RenderablePrimitives::SphereRenderer::~SphereRenderer()
{
	delete vertexBuffer;
	delete uVBuffer;
	delete indexBuffer;
	delete texture;
	delete shader;
}

void CommonObjects::RenderablePrimitives::SphereRenderer::CreateIndexBuffer(int rows, int columns)
{
	typedef unsigned short IndexType;
	std::vector<IndexType> indicies((rows - 1) * (columns - 1) * 6);
	auto iter = indicies.begin();
	for (int r = 0; r < rows - 1; r++) for (int s = 0; s < columns - 1; s++)
	{
		*iter++ = r * columns + s;
		*iter++ = (r + 1) * columns + s;
		*iter++ = (r + 1) * columns + (s + 1);

		*iter++ = r * columns + s;
		*iter++ = (r + 1) * columns + (s + 1);
		*iter++ = r * columns + (s + 1);
	}
	indexBuffer = new Render::IndexBuffer(indicies.size(), sizeof(IndexType), &indicies[0]);
}

void CommonObjects::RenderablePrimitives::SphereRenderer::CreateVertexBuffer(int rows, int columns)
{
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> uvs;

	verticies.resize(rows * columns);
	uvs.resize(rows * columns);

	auto vertexiter = verticies.begin();
	auto uviter = uvs.begin();

	float const rowStep = 1.0f / (rows - 1);
	float const columnStep = 1.0f / (columns - 1);
	for (int row = 0; row < rows; row++) for (int column = 0; column < columns; column++)
	{
		float y = std::sinf(-piOn2 + (pi * row * rowStep));
		float x = std::cosf(2.f * pi * column * columnStep) * std::sin(pi * row * rowStep);
		float z = std::sinf(2.f * pi * column * columnStep) * std::sin(pi * row * rowStep);
		*vertexiter++ = glm::vec3(x, y, z);
		*uviter++ = glm::vec2(row * rowStep, column * columnStep);
	}
	vertexBuffer = new Render::VectorBuffer(verticies.size(), 3, &verticies[0]);
	uVBuffer = new Render::VectorBuffer(uvs.size(), 2, &uvs[0]);
}

void CommonObjects::RenderablePrimitives::SphereRenderer::Draw(glm::dvec3 CameraPosition, glm::mat4x4 ViewProjection)
{
	// calculate transforms.
	glm::dvec3 trans = -CameraPosition + position;
	glm::mat4x4 WorldMatrix = glm::translate(glm::mat4x4(), glm::vec3(trans.x, trans.y, trans.z));
	glm::mat4x4 ModelMatrix = glm::scale(glm::mat4x4(), glm::vec3(radius, radius, radius)) * objectMatrix;
	
	// bind uniforms , buffers.
	shader->UseProgram();
	shader->ApplyMatrix("WorldMatrix", WorldMatrix);
	shader->ApplyMatrix("ModelMatrix", ModelMatrix);
	shader->ApplyMatrix("ViewProjectionMatrix", ViewProjection);
	shader->ApplyTexture("TextureSampler", *texture);

	// Bind buffers.
	vertexBuffer->BindBuffer(0);
	uVBuffer->BindBuffer(1);
	indexBuffer->BindBuffer();

	//draw
	shader->DrawIndexedElements(indexBuffer->GetNumberOfIndicies());

	// tidy up.
	vertexBuffer->DisableBuffer(0);
	uVBuffer->DisableBuffer(1);
}
