#pragma once
#include <glm\glm.hpp>
#include <memory>


class btCollisionShape;
struct btDefaultMotionState;
class btRigidBody;

class VectorAttributeBuffer;
class IndexBuffer;
class Shader;

class RenderMesh;

class Ball
{
private:
	bool Physics = false;
	std::unique_ptr<RenderMesh> mesh;
	btCollisionShape* ballShape;
	btDefaultMotionState* ballMotionState;
	btRigidBody* ballRigidBody;

	void CreateIndexBuffer(int rows, int columns);
	void CreateVertexBuffer(int rows, int columns);
	void SetupPhysics();

	glm::dvec3 Position;
	float radius;

public:
	void Draw(glm::dvec3 CameraPosition, glm::mat4x4 viewProjection);
	inline glm::dvec3 GetPosition(){ return Position; };

	Ball();
	Ball(glm::dvec3 centre, float radius , int rows , int columns , bool Physics);
	~Ball();
};

