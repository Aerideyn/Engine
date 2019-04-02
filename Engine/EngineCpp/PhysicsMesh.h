#pragma once
#include <memory>

class btBvhTriangleMeshShape;
class btTriangleIndexVertexArray;
struct btDefaultMotionState;
class btRigidBody;

class PhysicsMesh
{
private:
	bool isMeshReady = false;
	int numberOfTriangles;
	int numberOfVertices;
	int indexTypeSize;
	int* indexData;
	double* vertexData;

	// want to delay construction until our turn in the que.
	// what if data is not valid anymore? follows same convention of bullet. data needs to be maintained by owner of this object.

	btBvhTriangleMeshShape* physicsMeshShape;
	btTriangleIndexVertexArray* physicsMesh;
	btDefaultMotionState* motionState;
	btRigidBody* rigidBody;

public:
	PhysicsMesh(int numberOfTriangles, int* indexData, int IndexTypeSize, int numberOfVertices, double* vertexData);
	inline bool IsMeshReady(){ return isMeshReady; };
	void RegisterMesh();
	~PhysicsMesh();
};

