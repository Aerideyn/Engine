#pragma once
#include <glm/glm.hpp>
namespace CommonObjects
{
	class Controller
	{
	public:
		Controller();
		virtual ~Controller();

	protected:
		glm::mat4x4 ViewMatrix;
		glm::dvec3 Position;

	public:
		virtual void Update(double DeltaT);
		inline void SetPosition(glm::dvec3 position) { Position = position; };
		inline void SetViewMatrix(glm::mat4x4 matrix) { ViewMatrix = matrix; };
		inline glm::dvec3 GetPosition() { return Position; };
		inline glm::mat4x4 GetViewMatrix() { return ViewMatrix; };
	};
}