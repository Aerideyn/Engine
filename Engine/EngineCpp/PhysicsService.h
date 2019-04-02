#pragma once
#include <memory>

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btIDebugDraw;
class PhysicsMesh;
class PhysicsMeshProcessingQue;

class PhysicsService
{
	friend class Game;
public:
	PhysicsService();
	~PhysicsService();

private:
	void Update(double DeltaT);
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btIDebugDraw* debugDrawer;
	PhysicsMeshProcessingQue* meshProcessingQue;

public:
	void debugDraw();
	void SetGravity(double x, double y, double z);
	void AddRigidBody(btRigidBody* body);
	void RemoveRigidBody(btRigidBody* body);
	void SubmitMeshConstructionRequest(std::weak_ptr<PhysicsMesh> mesh);

};

