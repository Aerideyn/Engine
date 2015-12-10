#pragma once
#include <glm\glm.hpp>


class btCollisionShape;
struct btDefaultMotionState;
class btRigidBody;
namespace Physics{ class PhysicsWorld; };
namespace CommonObjects
{
	namespace PhysicsPrimitives
	{

		class PhysicsPrimative
		{
		public:
			virtual ~PhysicsPrimative(){};
			PhysicsPrimative(const Physics::PhysicsWorld& World) : world(World) {};

		protected:
			const Physics::PhysicsWorld& world;
			btCollisionShape* shape;
			btDefaultMotionState* motionState;
			btRigidBody* rigidBody;
			bool enabled;
			bool constructed;

		public:
			virtual glm::mat4x4 GetRotation() = 0;
			virtual glm::dvec3 GetPosition() = 0;
			virtual void SetLinearVelocity(glm::dvec3 v) = 0;
			virtual void Enable() = 0;
			virtual void Disable() = 0;
		};

		//====

		class PhysicsSphere : PhysicsPrimative
		{
		public:
			PhysicsSphere(const Physics::PhysicsWorld& World, glm::dvec3 Position, double radius, bool EnableCCD);
			~PhysicsSphere();
		public:
			virtual glm::mat4x4 GetRotation();
			virtual glm::dvec3 GetPosition();
			virtual void SetLinearVelocity(glm::dvec3 v);
			virtual void Enable();
			virtual void Disable();
		};

		class PhysicsCube : PhysicsPrimative
		{
		public:
			PhysicsCube(const Physics::PhysicsWorld& World);
			~PhysicsCube();
		public:
			virtual glm::mat4x4 GetRotation();
			virtual glm::dvec3 GetPosition();
			virtual void SetLinearVelocity(glm::dvec3 v);
			virtual void Enable();
			virtual void Disable();
		};
	}
}