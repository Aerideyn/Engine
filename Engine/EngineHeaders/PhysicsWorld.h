#pragma once
#include "glm\glm.hpp"

class btBroadphaseInterface;
class btDefaultCollisionConfiguration;
class btCollisionDispatcher;
class btSequentialImpulseConstraintSolver;
class btDiscreteDynamicsWorld;
class btRigidBody;
class btIDebugDraw;
class PhysicsMesh;
class PhysicsMeshProcessingQue;

namespace CommonObjects { class Camera; };
namespace Physics
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

	private:
		btBroadphaseInterface* broadphase;
		btDefaultCollisionConfiguration* collisionConfiguration;
		btCollisionDispatcher* dispatcher;
		btSequentialImpulseConstraintSolver* solver;
		btDiscreteDynamicsWorld* dynamicsWorld;
		btIDebugDraw* debugDrawer;
		PhysicsMeshProcessingQue* meshProcessingQue;

	public:
		void debugDraw(CommonObjects::Camera& camera);
		void Update(double DeltaT) const;
		void SetGravity(double x, double y, double z) const;
		void AddRigidBody(btRigidBody* body) const;
		void RemoveRigidBody(btRigidBody* body) const;
		glm::dvec3 Raycast(glm::dvec3 origin, glm::dvec3 direction);
	};
}