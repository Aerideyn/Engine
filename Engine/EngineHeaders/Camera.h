#pragma once
#include <glm\glm.hpp>
#include "BoundingFrustum.h"
namespace CommonObjects
{
	class Camera
	{
	public:
		Camera();
		~Camera();

	private:
		double fovDegrees;
		BoundingVolume::BoundingFrustum frustum;
		glm::dvec3 position;
		glm::mat4x4 ViewMatrix;
		glm::mat4x4 ProjectionMatrix;

	public:
		double GetFOVdegrees() const;
		double GetFOVradians() const;

		glm::dvec3 GetPosition() const;
		BoundingVolume::BoundingFrustum GetFrustum() const;
		glm::mat4x4 GetProjectionMatrix() const;
		glm::mat4x4 GetViewMatrix() const;

		void SetViewMatrix(glm::mat4x4 matrix);
		void SetPosition(glm::dvec3 Position);
	};
}
