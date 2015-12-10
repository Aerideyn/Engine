#include "PhysicsWorld.h"
#include "PhysicsDebugDrawer.h"
#include <btBulletDynamicsCommon.h>

Physics::PhysicsWorld::PhysicsWorld()
{
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver();
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0.0,-9.8, 0.0));
}

Physics::PhysicsWorld::~PhysicsWorld()
{
	delete dynamicsWorld;
	delete solver;
	delete dispatcher;
	delete collisionConfiguration;
	delete broadphase;
	if (debugDrawer == nullptr) delete debugDrawer;
}

void Physics::PhysicsWorld::debugDraw(CommonObjects::Camera& camera)
{
	if (debugDrawer == nullptr)
	{
		debugDrawer = new PhysicsDebugDrawer(camera);
		dynamicsWorld->setDebugDrawer(debugDrawer);
		debugDrawer->setDebugMode(1);
	}
		dynamicsWorld->debugDrawWorld();
}

void Physics::PhysicsWorld::Update(double DeltaT) const
{
	dynamicsWorld->stepSimulation(DeltaT, 2);
}

void Physics::PhysicsWorld::SetGravity(double x, double y, double z) const
{
	dynamicsWorld->setGravity(btVector3(x, y, z));
}

void Physics::PhysicsWorld::AddRigidBody(btRigidBody* body) const
{
	dynamicsWorld->addRigidBody(body);
}

void Physics::PhysicsWorld::RemoveRigidBody(btRigidBody* body) const
{
	dynamicsWorld->removeRigidBody(body);
}

glm::dvec3 Physics::PhysicsWorld::Raycast(glm::dvec3 Origin, glm::dvec3 Direction)
{
	Direction *= 1000;
	btVector3 Start = btVector3(Origin.x, Origin.y, Origin.z);
	btVector3 End = btVector3(Origin.x + Direction.x, Origin.y + Direction.y, Origin.z + Direction.z);
	btCollisionWorld::ClosestRayResultCallback RayCallback(Start, End);
	dynamicsWorld->rayTest(Start, End,RayCallback);
	if (RayCallback.hasHit())
	{
		btVector3 point = RayCallback.m_hitPointWorld;
		return glm::dvec3(point.getX(), point.getY(), point.getZ());
	}
	else
	{
		return Origin;
	}
}