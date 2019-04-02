#pragma once
#include <glm\glm.hpp>

class RenderMesh;

class BoundingSphere
{

private:
	static RenderMesh* mesh;
	void BuildMesh();

	void CreateIndexBuffer(int rows, int columns);
	void CreateVertexBuffer(int rows, int columns);

public:

	double Radius;
	glm::dvec3 Centre;

	BoundingSphere(glm::dvec3 centre, double radius);
	inline BoundingSphere() { Radius = 0; Centre = glm::dvec3(); };
	~BoundingSphere();

	void Draw(glm::dvec3 CameraPosition, glm::mat4x4 viewProjection);
};

