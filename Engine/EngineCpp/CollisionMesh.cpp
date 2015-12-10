#include "CollisionMesh.h"
#include "PhysicsWorld.h"
#include <btBulletDynamicsCommon.h>

Physics::CollisionMesh::CollisionMesh()
{
	numberOfIndices = 0;
	numberOfVertices = 0;
	constructed = false;
	enabled = false;
}

Physics::CollisionMesh::CollisionMesh(PhysicsWorld const* World, int NumberOfIndices, int* IndexData, int NumberOfVertices, double* VertexData) : world(World)
{
	numberOfIndices = NumberOfIndices;
	numberOfVertices = NumberOfVertices;
	indexData = IndexData;
	vertexData = VertexData;
	constructed = false;
	enabled = false;
}

Physics::CollisionMesh::~CollisionMesh()
{
	if (enabled && world != nullptr) world->RemoveRigidBody(rigidBody);
	if (constructed)
	{
		delete rigidBody;
		delete motionState;
		delete physicsMeshShape;
		delete physicsMesh;
	}
}

void Physics::CollisionMesh::Construct()
{
	if (!constructed && numberOfIndices > 0 && numberOfVertices > 0)
	{
		physicsMesh = new btTriangleIndexVertexArray(numberOfIndices / 3, indexData, sizeof(int)* 3, numberOfVertices, vertexData, sizeof(double)* 3);
		physicsMeshShape = new btBvhTriangleMeshShape(physicsMesh,true, true);
		motionState = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo info(0, motionState, physicsMeshShape, btVector3(0.0, 0.0, 0.0));
		rigidBody = new btRigidBody(info);
		rigidBody->setFriction(1);
		rigidBody->setRollingFriction(1);
		rigidBody->setRestitution(1);
		constructed = true;
	}
	Enable();
}

void Physics::CollisionMesh::Enable()
{
	if (world != nullptr && constructed == true && enabled == false)
	{
		world->AddRigidBody(rigidBody);
		enabled = true;
	}
}

void Physics::CollisionMesh::Disable()
{
	if (world != nullptr && enabled == true)
	{
		world->RemoveRigidBody(rigidBody);
		enabled = false;
	}
}
