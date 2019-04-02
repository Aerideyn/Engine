#include "PhysicsService.h"
#include "PhysicsDebugRenderer.h"
#include "PhysicsMeshProcessingQue.h"
#include <btBulletDynamicsCommon.h>


PhysicsService::PhysicsService()
{
	broadphase = new btDbvtBroadphase();

	collisionConfiguration = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver();

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(-1.6, 0.0, 0.0));

	debugDrawer = new PhysicsDebugRenderer();

	meshProcessingQue = new PhysicsMeshProcessingQue();

	//dynamicsWorld->setDebugDrawer(debugDrawer);
}


PhysicsService::~PhysicsService()
{
	//delete debugDrawer;
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
	delete meshProcessingQue;
}

void PhysicsService::Update(double DeltaT)
{
	dynamicsWorld->stepSimulation(DeltaT, 2);
}

void PhysicsService::SetGravity(double x, double y , double z)
{
	dynamicsWorld->setGravity(btVector3(x, y, z));
}

void PhysicsService::debugDraw()
{
	//dynamicsWorld->debugDrawWorld();
}

void PhysicsService::AddRigidBody(btRigidBody* body)
{
	dynamicsWorld->addRigidBody(body);
}

void PhysicsService::RemoveRigidBody(btRigidBody* body)
{
	dynamicsWorld->removeRigidBody(body);
}

void PhysicsService::SubmitMeshConstructionRequest(std::weak_ptr<PhysicsMesh> mesh)
{
	meshProcessingQue->SubmitJob(mesh);
}