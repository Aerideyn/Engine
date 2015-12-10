#pragma once
#include <glm\glm.hpp>

namespace Render
{
	class VectorBuffer;
	class IndexBuffer;
	class Shader;
	class Texture2D;
}

namespace CommonObjects 
{
	namespace RenderablePrimitives
	{
		class SphereRenderer
		{
		public:
			SphereRenderer();
			SphereRenderer(glm::dvec3 centre, double radius, int rows, int columns);
			~SphereRenderer();

		private:
			glm::dvec3 position;
			double radius;
			glm::mat4x4 objectMatrix;

			Render::Shader* shader;
			Render::Texture2D* texture;
			Render::VectorBuffer* vertexBuffer;
			Render::VectorBuffer* uVBuffer;
			Render::IndexBuffer* indexBuffer;

			void CreateIndexBuffer(int rows, int columns);
			void CreateVertexBuffer(int rows, int columns);

		public:
			glm::dvec3 GetPosition() { return position; };
			void SetPosition(glm::dvec3 Position) { position = Position; };
			void SetObjectMatrix(glm::mat4x4 matrix) { objectMatrix = matrix; };
			void Draw(glm::dvec3 CameraPosition, glm::mat4x4 viewProjection);
		};
	}
}
