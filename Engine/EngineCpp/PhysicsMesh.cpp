#include "PhysicsMesh.h"
#include "Game.h"
#include "PhysicsService.h"
#include <btBulletDynamicsCommon.h>

PhysicsMesh::PhysicsMesh(int NumberOfTriangles , int* IndexData , int IndexTypeSize , int NumberOfVertices , double* VertexData)
{
	numberOfTriangles = NumberOfTriangles;
	numberOfVertices = NumberOfVertices;
	indexTypeSize = IndexTypeSize;
	indexData = IndexData;
	vertexData = VertexData;
}

void PhysicsMesh::RegisterMesh()
{
	physicsMesh = new btTriangleIndexVertexArray(numberOfTriangles, indexData, indexTypeSize * 3, numberOfVertices, vertexData, sizeof(double)* 3);
	physicsMeshShape = new btBvhTriangleMeshShape(physicsMesh, true, true);
	motionState = new btDefaultMotionState();

	btRigidBody::btRigidBodyConstructionInfo info(0, motionState, physicsMeshShape, btVector3(0.0, 0.0, 0.0));
	rigidBody = new btRigidBody(info);
	rigidBody->setFriction(1);
	rigidBody->setRollingFriction(1);
	rigidBody->setRestitution(1);
	Game::GetPhysicsService().AddRigidBody(rigidBody);
	isMeshReady = true;
}

PhysicsMesh::~PhysicsMesh()
{
	if (isMeshReady)
	{
		Game::GetPhysicsService().RemoveRigidBody(rigidBody);
		delete rigidBody;
		delete motionState;
		delete physicsMeshShape;
		delete physicsMesh;
	}
}
