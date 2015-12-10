#pragma once
#include "glm\glm.hpp"

namespace BoundingVolume{
	class BoundingSphere;
	class BoundingBox;
	class BoundingFrustum
	{
	public:
		BoundingFrustum();
		BoundingFrustum(glm::mat4x4 FrustumMatrix, glm::dvec3 Translation);
		~BoundingFrustum();

	private:
		float frustum[6][4];
		glm::dvec3 translation;
	public:
		bool IntersectsBoundingSphere(const BoundingSphere& sphere) const;
		bool IntersectsBoundingFrustum(const BoundingFrustum& frustum) const;
		bool IntersectsBoundingBox(const BoundingBox& box) const;

	};
}