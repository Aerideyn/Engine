#pragma once
#include <glm/glm.hpp>
#include <memory>

class Camera;

class Controller
{
private:
	std::weak_ptr<Camera> ptr_AttachedCamera;
	
protected:
	glm::mat4x4 ViewMatrix;
	glm::dvec3 Position;
	
public:
	Controller();
	virtual ~Controller();
	virtual void Update(double DeltaT);

	inline glm::dvec3 GetPosition() { return Position; };
	inline void SetPosition(glm::dvec3 position) { Position = position; };

	inline glm::mat4x4 GetViewMatrix() { return ViewMatrix; };

	void AttachCamera(std::shared_ptr<Camera> camera);
	inline void DetatchCamera(){ ptr_AttachedCamera.reset(); };

};
