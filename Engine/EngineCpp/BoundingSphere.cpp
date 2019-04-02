#include "BoundingSphere.h"
#include "GL\glew.h"
#include "RenderMesh.h"
#include <glm\gtc\matrix_transform.hpp>

const int segments = 50;
RenderMesh* BoundingSphere::mesh = nullptr;

BoundingSphere::BoundingSphere(glm::dvec3 centre, double radius) : Centre(centre), Radius(radius)
{

}


BoundingSphere::~BoundingSphere()
{

}

void BoundingSphere::CreateVertexBuffer(int rows, int columns)
{
	mesh = new RenderMesh("Shaders/LineVertex.vertexshader", "Shaders/LineFragment.fragmentshader");
	float const pi = 3.1415926535897932384626433832795f;
	float const piOn2 = 1.5707963267948966192313216916398f;

	std::vector<glm::vec3> verticies;
	std::vector<glm::vec3> colors;

	verticies.resize(rows * columns);
	colors.resize(rows*columns);

	auto vertexiter = verticies.begin();
	auto citer = colors.begin();

	float const rowStep = 1.0f / (rows - 1);
	float const columnStep = 1.0f / (columns - 1);
	for (int row = 0; row < rows; row++) for (int column = 0; column < columns; column++)
	{
		float y = std::sinf(-piOn2 + (pi * row * rowStep));
		float x = std::cosf(2.f * pi * column * columnStep) * std::sin(pi * row * rowStep);
		float z = std::sinf(2.f * pi * column * columnStep) * std::sin(pi * row * rowStep);
		*vertexiter++ = glm::vec3(x, y, z);
		*citer++ = glm::vec3(1, 0, 0);
	}
	mesh->SetVerticies(verticies);
	mesh->SetNormals(colors);
	mesh->SetDrawMode(MeshDrawMode::Lines);
}

void BoundingSphere::CreateIndexBuffer(int rows, int columns)
{
	typedef unsigned short IndexType;
	std::vector<IndexType> indicies((rows)* (columns)* 6);
	auto iter = indicies.begin();
	for (int r = 0; r < rows; r++) for (int s = 0; s < columns; s++)
	{
		*iter++ = r * columns + s;
		*iter++ = (r + 1) * columns + s;
		*iter++ = (r + 1) * columns + (s + 1);

		*iter++ = r * columns + s;
		*iter++ = (r + 1) * columns + (s + 1);
		*iter++ = r * columns + (s + 1);
	}
	mesh->SetIndicies(indicies);
}

void BoundingSphere::BuildMesh()
{
	mesh = new RenderMesh("Shaders/LineVertex.vertexshader", "Shaders/LineFragment.fragmentshader");
	double const pi = 3.1415926535897932384626433832795f;
	double const piOn2 = 1.5707963267948966192313216916398f;
	double step = 1.0 / (segments - 1);
	std::vector<glm::vec3> vertices(segments*3);
	std::vector<glm::vec3> colors(segments*3);
	int index = 0;
	for (int i = 0; i < segments; i++)
	{
		float x = static_cast<float>(std::cos(2 * pi * i * step));
		float y = 0;
		float z= static_cast<float>(std::sin(2 * pi * i * step));
		vertices[index] = glm::vec3(x, y, z);
		colors[index] = glm::vec3(0.0f, 1.0f, 0.0f);
		index++;
	}

	for (int i = 0; i < segments; i++)
	{
		float x = 0;
		float y = static_cast<float>(std::cos(2 * pi * i * step));
		float z = static_cast<float>(std::sin(2 * pi * i * step));
		vertices[index] = glm::vec3(x, y, z);
		colors[index] = glm::vec3(1.0f, 0.0f, 0.0f);
		index++;
	}

	for (int i = 0; i < segments; i++)
	{
		float x = static_cast<float>(std::cos(2 * pi * i * step));
		float y = static_cast<float>(std::sin(2 * pi * i * step));
		float z = 0;
		vertices[index] = glm::vec3(x, y, z);
		colors[index] = glm::vec3(0.0f, 0.0f, 1.0f);
		index++;
	}

	mesh->SetVerticies(vertices);
	mesh->SetNormals(colors);
	mesh->SetDrawMode(MeshDrawMode::Lines);
}

void BoundingSphere::Draw(glm::dvec3 CameraPosition, glm::mat4x4 viewProjection)
{
	if (mesh == nullptr)
	{
		BuildMesh();
		//CreateVertexBuffer(10,10);
		//CreateIndexBuffer(10,10);
	}
	mesh->SetModelMatrix(glm::scale(glm::mat4x4(), glm::vec3(Radius, Radius, Radius)));
	mesh->SetWorldMatrix(Centre - CameraPosition);
	mesh->SetViewProjectionMatrix(viewProjection);
	mesh->Draw();
}

