#pragma once
#include "glm\glm.hpp"
#include <vector> 

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
		class VectorRenderer
		{
		public:
			VectorRenderer(glm::dvec3 Start, glm::dvec3 End, glm::vec3 Color);
			~VectorRenderer();

		private:
			std::vector<glm::vec3> verts;
			std::vector<glm::vec3> cols;


			glm::dvec3 Origin;
			Render::Shader* DebugRenderShader;
			Render::VectorBuffer* DebugRenderVerts;
			Render::VectorBuffer* DebugRenderColors;

		public:
			void Render(const CommonObjects::Camera& camera);
			void AddVector(glm::dvec3 Start, glm::dvec3 Stop, glm::vec3 Color);
		};
	}
}