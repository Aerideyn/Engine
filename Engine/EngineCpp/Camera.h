#pragma once
#include <glm\glm.hpp>
#include "Controller.h"
#include <memory>

class BoundingSphere;

class Camera
{
private:

	double FieldOfView_degrees;

	glm::mat4x4 Projection;
	glm::mat4x4 View;
	glm::dvec3 Position;

public:
	Camera();
	~Camera();

	inline void SetViewMatrix(glm::mat4x4 ViewMatrix) { View = ViewMatrix; };
	inline glm::mat4x4 GetViewMatrix() { return View; };

	inline void SetProjectionMatrix(glm::mat4x4 ProjectionMatrix) { Projection = ProjectionMatrix; };
	inline glm::mat4x4 GetProjectionMatrix(){ return Projection; };

	inline void SetPosition(glm::dvec3 position) { Position = position; };
	inline glm::dvec3 GetPosition() { return Position; };

	// Set field of view in degrees.
	inline void SetFieldOfView(double fovD) { FieldOfView_degrees = fovD; }; // multiply by pi / 180.

	// Returns the field of view in degrees.
	inline double GetFieldOfViewD() { return FieldOfView_degrees; };

	// Returns the field of veiw in radians.
	inline double GetFieldOfViewR() { return FieldOfView_degrees * 0.01745329251994329576923690768489; };

	bool BoundingSphereInFrustum(const BoundingSphere& sphere);

};

