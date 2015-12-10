#include "PhysicsDebugDrawer.h"
#include "VectorRenderer.h"
#include "Camera.h"
#include "GL\glew.h"
#include "VectorRenderer.h"

Physics::PhysicsDebugDrawer::PhysicsDebugDrawer(CommonObjects::Camera& cam) : camera(cam)
{
}

Physics::PhysicsDebugDrawer::~PhysicsDebugDrawer()
{
}

void Physics::PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	glm::dvec3 A = glm::dvec3(to.getX(), to.getY(), to.getZ());
	glm::dvec3 B = glm::dvec3(from.getX(), from.getY(), from.getZ());
	glm::vec3 Color = glm::vec3(fromColor.getX(), fromColor.getY(), fromColor.getZ());
	CommonObjects::RenderablePrimitives::VectorRenderer r = CommonObjects::RenderablePrimitives::VectorRenderer(A, B, Color);
	r.Render(camera);
}

void Physics::PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	glm::dvec3 A = glm::dvec3(to.getX(), to.getY(), to.getZ());
	glm::dvec3 B = glm::dvec3(from.getX(), from.getY(), from.getZ());
	glm::vec3 Color = glm::vec3(color.getX(), color.getY(), color.getZ());
	CommonObjects::RenderablePrimitives::VectorRenderer r = CommonObjects::RenderablePrimitives::VectorRenderer(A, B, Color);
	r.Render(camera);
}

void Physics::PhysicsDebugDrawer::drawSphere(const btVector3& p, btScalar radius, const btVector3& color)
{}

void Physics::PhysicsDebugDrawer::drawTriangle(const btVector3& a, const btVector3& b, const btVector3& c, const btVector3& color, btScalar alpha)
{
	glm::dvec3 A = glm::dvec3(a.getX(), a.getY(), a.getZ());
	glm::dvec3 B = glm::dvec3(b.getX(), b.getY(), b.getZ());
	glm::dvec3 C = glm::dvec3(c.getX(), c.getY(), c.getZ());
	glm::vec3 Color = glm::vec3(color.getX(), color.getY(), color.getZ());
	CommonObjects::RenderablePrimitives::VectorRenderer r = CommonObjects::RenderablePrimitives::VectorRenderer(A, B, Color);
	r.AddVector(B, C, Color);
	r.AddVector(C, A, Color);
	r.Render(camera);
}

void Physics::PhysicsDebugDrawer::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{}

void Physics::PhysicsDebugDrawer::reportErrorWarning(const char* warningString)
{}

void Physics::PhysicsDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{}

void Physics::PhysicsDebugDrawer::setDebugMode(int debugMode)
{
	m_debugMode = debugMode;
}