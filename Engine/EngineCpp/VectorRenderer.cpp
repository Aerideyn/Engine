#include "VectorRenderer.h"
#include "AttributeBuffers.h"
#include "Shader.h"
#include "Camera.h"
#include <glm\gtc\matrix_transform.hpp>

CommonObjects::RenderablePrimitives::VectorRenderer::VectorRenderer(glm::dvec3 Start, glm::dvec3 End, glm::vec3 Color) : Origin(Start)
{
	verts = std::vector<glm::vec3>();
	cols = std::vector<glm::vec3>();

	verts.push_back(glm::vec3(0, 0, 0));
	verts.push_back(glm::vec3(End - Start));
	cols.push_back(Color);
	cols.push_back(Color);

	DebugRenderVerts = new Render::VectorBuffer(2, 3, &verts[0]);
	DebugRenderColors = new Render::VectorBuffer(2, 3, &cols[0]);
	DebugRenderShader = new Render::Shader("Shaders/Line.vertexshader", "Shaders/Line.fragmentshader");
}


CommonObjects::RenderablePrimitives::VectorRenderer::~VectorRenderer()
{
	delete DebugRenderColors;
	delete DebugRenderShader;
	delete DebugRenderVerts;
}

void CommonObjects::RenderablePrimitives::VectorRenderer::AddVector(glm::dvec3 Start, glm::dvec3 End, glm::vec3 Color)
{
	verts.push_back(glm::vec3(Start - Origin));
	verts.push_back(glm::vec3(End - Origin));
	cols.push_back(Color);
	cols.push_back(Color);

	delete DebugRenderVerts;
	delete DebugRenderColors;

	DebugRenderVerts = new Render::VectorBuffer(verts.size(), 3, &verts[0]);
	DebugRenderColors = new Render::VectorBuffer(cols.size(), 3, &cols[0]);
}

void CommonObjects::RenderablePrimitives::VectorRenderer::Render(const Camera& camera)
{
	glm::dvec3 trans = -camera.GetPosition() + Origin;
	glm::mat4x4 WorldMatrix = glm::translate(glm::mat4x4(), glm::vec3(trans.x, trans.y, trans.z));
	glm::mat4x4 viewProjection = camera.GetProjectionMatrix() * camera.GetViewMatrix();

	// set our shader.
	DebugRenderShader->UseProgram();

	// set world matrix;
	DebugRenderShader->ApplyMatrix("ModelMatrix", glm::mat4x4());
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