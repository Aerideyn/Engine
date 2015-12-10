#pragma once
class btBvhTriangleMeshShape;
class btTriangleIndexVertexArray;
struct btDefaultMotionState;
class btRigidBody;


namespace Physics
{
	class PhysicsWorld;
	class CollisionMesh
	{
	public:
		CollisionMesh();
		CollisionMesh(PhysicsWorld const* World, int NumberOfIndices, int* IndexData, int NumberOfVertices, double* VertexData);
		~CollisionMesh();

	private:
		PhysicsWorld const* world;
		int numberOfIndices;
		int numberOfVertices;
		int* indexData;
		double* vertexData;

		bool enabled;
		bool constructed;

		btBvhTriangleMeshShape* physicsMeshShape;
		btTriangleIndexVertexArray* physicsMesh;
		btDefaultMotionState* motionState;
		btRigidBody* rigidBody;

	public:
		void Construct();
		bool IsEnabled(){ return enabled; };
		void Enable();
		void Disable();
	};
}
