#include "Ball.h"
#include "AttributeBuffer.h"
#include "Shader.h"

#include <vector>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <btBulletDynamicsCommon.h>

#include "RenderMesh.h"
#include "Game.h"
#include "PhysicsService.h"

float const pi = 3.1415926535897932384626433832795f;
float const piOn2 = 1.5707963267948966192313216916398f;

void Ball::CreateVertexBuffer(int rows, int columns)
{
	std::vector<glm::vec3> verticies;
	std::vector<glm::vec2> uvs;

	verticies.resize(rows * columns);
	uvs.resize(rows*columns);

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
	mesh->SetVerticies(verticies);
	mesh->SetUVCoordinates(uvs);
}

void Ball::CreateIndexBuffer(int rows, int columns)
{
	typedef unsigned short IndexType;
	std::vector<IndexType> indicies((rows-1) * (columns-1) * 6);
	auto iter = indicies.begin();
	for (int r = 0; r < rows-1; r++) for (int s = 0; s < columns-1; s++)
	{
		*iter++ =  r * columns + s;
		*iter++ = (r + 1) * columns + s;
		*iter++ = (r + 1) * columns + (s + 1);

		*iter++ = r * columns + s;
		*iter++ = (r + 1) * columns + (s + 1);
		*iter++ = r * columns + (s + 1);
	}
	mesh->SetIndicies(indicies);
}

Ball::Ball()
{
	Position = glm::dvec3();
	radius = 1.0;

	mesh = std::unique_ptr<RenderMesh>(new RenderMesh("Shaders/BasicVertex.vertexshader", "Shaders/BasicFragment.fragmentshader"));
	mesh->AddTexture("Textures/MissingTex.jpg", "TextureSampler");

	CreateVertexBuffer(3, 3);
	CreateIndexBuffer(3, 3);
	SetupPhysics();
}

Ball::Ball(glm::dvec3 centre, float Radius, int Rows, int Columns , bool physics)
{
	Position = centre;
	radius = Radius;

	mesh = std::unique_ptr<RenderMesh>(new RenderMesh("Shaders/BasicVertex.vertexshader", "Shaders/BasicFragment.fragmentshader"));
	mesh->AddTexture("Textures/stone.jpg", "TextureSampler");

	CreateVertexBuffer(Rows, Columns);
	CreateIndexBuffer(Rows, Columns);
	if (physics)SetupPhysics();

}

Ball::~Ball()
{
	if (Physics)
	{
		Game::GetPhysicsService().RemoveRigidBody(ballRigidBody);
		delete ballRigidBody;
		delete ballMotionState;
		delete ballShape;
	}
}

void Ball::SetupPhysics()
{
	Physics = true;
	ballShape = new btSphereShape(radius);

	ballMotionState = new btDefaultMotionState(btTransform(btQuaternion(0.0, 0.0, 0.0, 1.0), btVector3(Position.x, Position.y, Position.z)));

	btScalar mass = 1.0;
	btVector3 inertia;
	ballShape->calculateLocalInertia(1.0, inertia);

	btRigidBody::btRigidBodyConstructionInfo ballbodyCI(mass, ballMotionState, ballShape, inertia);
	ballRigidBody = new btRigidBody(ballbodyCI);

	Game::GetPhysicsService().AddRigidBody(ballRigidBody);

	ballRigidBody->applyImpulse(btVector3(0.0, 0.0, 10.0), btVector3(0.0,0.0,0.0));
	ballRigidBody->setFriction(1);
	ballRigidBody->setRollingFriction(1);
	ballRigidBody->setRestitution(0.25);
}

void Ball::Draw(glm::dvec3 CameraPosition, glm::mat4x4 viewProjection)
{
	glm::mat4x4 rotation = glm::mat4x4();
	if (Physics)
	{
		btTransform transform;
		ballRigidBody->getMotionState()->getWorldTransform(transform);
		
		btVector3 pos = transform.getOrigin();
		Position.x = pos.getX();
		Position.y = pos.getY();
		Position.z = pos.getZ();

		btScalar data[16];
		transform.getOpenGLMatrix(&data[0]);
		data[12] = 0.0; data[13] = 0.0; data[14] = 0.0;
		rotation = glm::make_mat4x4(data);
	}

	// scale as needed.
	glm::mat4x4 ModelMatrix = glm::scale(glm::mat4x4(), glm::vec3(radius, radius, radius)) * rotation;

	// bind uniforms , buffers.
	mesh->SetModelMatrix(ModelMatrix);
	mesh->SetViewProjectionMatrix(viewProjection);
	mesh->SetWorldMatrix(-CameraPosition + Position);
	mesh->DrawMesh();
}