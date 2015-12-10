#pragma once
#include <glm\glm.hpp>

namespace Render
{
	class VectorBuffer;
	class Shader;
}

namespace CommonObjects
{
	class Camera;
	namespace RenderablePrimitives
	{
		class AxisRenderer
		{
		public:
			AxisRenderer(glm::dvec3 Position, glm::mat4x4 RotationMatrix);
			~AxisRenderer();

		private:
			glm::dvec3 Origin;
			glm::mat4x4 rotation;
			Render::Shader* DebugRenderShader;
			Render::VectorBuffer* DebugRenderVerts;
			Render::VectorBuffer* DebugRenderColors;

		public:
			void Render(Camera& camera);
			void SetPosition(glm::dvec3 Position) { Origin = Position; };
			void SetRotation(glm::mat4x4 RotationMatrix) { rotation = RotationMatrix; };
		};
	}
}