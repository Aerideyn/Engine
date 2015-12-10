#include "AxisRenderer.h"
#include "AttributeBuffers.h"
#include "Shader.h"
#include "Camera.h"
#include <vector>
#include <glm\gtc\matrix_transform.hpp>

CommonObjects::RenderablePrimitives::AxisRenderer::AxisRenderer(glm::dvec3 Position, glm::mat4x4 RotationMatrix)
{
	Origin = Position;
	rotation = RotationMatrix;

	std::vector<glm::vec3> verts = std::vector<glm::vec3>();
	std::vector<glm::vec3> cols = std::vector<glm::vec3>();

	verts.push_back(glm::vec3(0, 0, 0));
	verts.push_back(glm::vec3(10, 0, 0));
	verts.push_back(glm::vec3(0, 0, 0));
	verts.push_back(glm::vec3(0, 10, 0));
	verts.push_back(glm::vec3(0, 0, 0));
	verts.push_back(glm::vec3(0, 0, -10));

	cols.push_back(glm::vec3(1, 0, 0));
	cols.push_back(glm::vec3(1, 0, 0));
	cols.push_back(glm::vec3(0, 1, 0));
	cols.push_back(glm::vec3(0, 1, 0));
	cols.push_back(glm::vec3(0, 0, 1));
	cols.push_back(glm::vec3(0, 0, 1));

	DebugRenderVerts = new Render::VectorBuffer(6, 3, &verts[0]);
	DebugRenderColors = new Render::VectorBuffer(6, 3, &cols[0]);
	DebugRenderShader = new Render::Shader("Shaders/Line.vertexshader", "Shaders/Line.fragmentshader");
}


CommonObjects::RenderablePrimitives::AxisRenderer::~AxisRenderer()
{
	delete DebugRenderColors;
	delete DebugRenderShader;
	delete DebugRenderVerts;
}

void CommonObjects::RenderablePrimitives::AxisRenderer::Render(Camera& camera)
{
	glm::dvec3 trans = -camera.GetPosition() + Origin;
	glm::mat4x4 WorldMatrix = glm::translate(glm::mat4x4(), glm::vec3(trans.x, trans.y, trans.z));
	glm::mat4x4 viewProjection = camera.GetProjectionMatrix() * camera.GetViewMatrix();

	// set our shader.
	DebugRenderShader->UseProgram();

	// set world matrix;
	DebugRenderShader->ApplyMatrix("ModelMatrix", rotation);
	DebugRenderShader->ApplyMatrix("WorldMatrix", WorldMatrix);
	DebugRenderShader->ApplyMatrix("ViewProjectionMatrix", viewProjection);

	// Bind buffers.
	DebugRenderVerts->BindBuffer(0);
	DebugRenderColors->BindBuffer(1);

	//draw
	DebugRenderShader->DrawNonIndexedElements(DebugRenderVerts->GetElementCount(), true);

	// tidy up.
	DebugRenderVerts->DisableBuffer(0);
	DebugRenderColors->DisableBuffer(1);
}