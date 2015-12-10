#pragma once
#include <glm\glm.hpp>
namespace BoundingVolume{
	class BoundingBox;
	class BoundingFrustum;
	class BoundingSphere
	{
	public:
		BoundingSphere();
		BoundingSphere(double Radius, glm::dvec3 Centre);
		~BoundingSphere();

	public:
		double radius;
		glm::dvec3 centre;
		bool IntersectsBoundingFrustum(const BoundingFrustum& frustum) const;
		bool IntersectsBoundingBox(const BoundingBox& box) const;
		bool IntersectsBoundingSphere(const BoundingSphere& sphere) const;
	};
}
