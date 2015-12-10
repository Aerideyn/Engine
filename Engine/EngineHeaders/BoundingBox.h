#pragma once
#include <glm\glm.hpp>

namespace BoundingVolume{
	class BoundingSphere;
	class BoundingFrustum;

	class BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox(glm::dvec3 Min, glm::dvec3 Max);
		~BoundingBox();
	public:
		bool IntersectsBoundingFrustum(const BoundingFrustum& frustum);
		bool IntersectsBoundingBox(const BoundingBox& box);
		bool IntersectsBoundingSphere(const BoundingSphere& sphere);
		bool ContainsPoint(glm::dvec3 Point);
	public:
		glm::dvec3 min;
		glm::dvec3 max;
	};
}
