#include "PhysicsWorld.h"
#include "PhysicsPrimitives.h"
#include <btBulletDynamicsCommon.h>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

bool alternate = false;

CommonObjects::PhysicsPrimitives::PhysicsSphere::PhysicsSphere(const Physics::PhysicsWorld& World, glm::dvec3 Position, double radius, bool enableCCD) : PhysicsPrimative(World)
{
	shape = new btSphereShape(radius);
	motionState = new btDefaultMotionState(btTransform(btQuaternion(0.0, 0.0, 0.0, 1.0), btVector3(Position.x, Position.y, Position.z)));
	btScalar mass = 1.0;
	btVector3 inertia;
	shape->calculateLocalInertia(1.0, inertia);
	btRigidBody::btRigidBodyConstructionInfo ballbodyCI(mass, motionState, shape, inertia);
	rigidBody = new btRigidBody(ballbodyCI);
	
	// enable continuous collision detection
	if (enableCCD)
	{
		rigidBody->setCcdMotionThreshold(radius);
		rigidBody->setCcdSweptSphereRadius(radius / 5.0);
	}
}

CommonObjects::PhysicsPrimitives::PhysicsSphere::~PhysicsSphere()
{
	delete rigidBody;
	delete motionState;
	delete shape;
}

glm::dvec3 CommonObjects::PhysicsPrimitives::PhysicsSphere::GetPosition()
{
	btTransform transform;
	rigidBody->getMotionState()->getWorldTransform(transform);
	btVector3 pos = transform.getOrigin();
	return glm::dvec3(pos.getX(), pos.getY(), pos.getZ());
}

glm::mat4x4 CommonObjects::PhysicsPrimitives::PhysicsSphere::GetRotation()
{
	glm::mat4x4 rotation = glm::mat4x4();
	btTransform transform;
	rigidBody->getMotionState()->getWorldTransform(transform);
	btScalar data[16];
	transform.getOpenGLMatrix(&data[0]);
	data[12] = 0.0; data[13] = 0.0; data[14] = 0.0;
	rotation = glm::make_mat4x4(data);
	return rotation;
}

void CommonObjects::PhysicsPrimitives::PhysicsSphere::SetLinearVelocity(glm::dvec3 v)
{
	rigidBody->setLinearVelocity(btVector3(v.x, v.y, v.z));
}

void CommonObjects::PhysicsPrimitives::PhysicsSphere::Enable()
{
	world.AddRigidBody(rigidBody);
}

void CommonObjects::PhysicsPrimitives::PhysicsSphere::Disable()
{
	world.RemoveRigidBody(rigidBody);
}