#include "BoundingSphere.h"
#include "BoundingFrustum.h"
#include "BoundingBox.h"

BoundingVolume::BoundingSphere::BoundingSphere() : radius(1), centre(glm::dvec3(0.0, 0.0, 0.0)){}
BoundingVolume::BoundingSphere::BoundingSphere(double Radius, glm::dvec3 Centre) : radius(Radius), centre(Centre){}


BoundingVolume::BoundingSphere::~BoundingSphere()
{
}

bool BoundingVolume::BoundingSphere::IntersectsBoundingBox(const BoundingBox& box) const
{
	double dmin = 0;

	if (centre.x < box.min.x) {
		dmin += pow(centre.x - box.min.x, 2);
	}
	else if (centre.x > box.max.x) {
		dmin += pow(centre.x - box.max.x, 2);
	}

	if (centre.y < box.min.y) {
		dmin += pow(centre.y - box.min.y, 2);
	}
	else if (centre.y > box.max.y) {
		dmin += pow(centre.y - box.max.y, 2);
	}

	if (centre.z < box.min.z) {
		dmin += pow(centre.z - box.min.z, 2);
	}
	else if (centre.z > box.max.z) {
		dmin += pow(centre.z - box.max.z, 2);
	}

	return dmin <= pow(radius, 2);
}

bool BoundingVolume::BoundingSphere::IntersectsBoundingFrustum(const BoundingFrustum& frustum) const
{
	return frustum.IntersectsBoundingSphere(*this);
}

bool BoundingVolume::BoundingSphere::IntersectsBoundingSphere(const BoundingSphere& sphere) const
{
	return true;
}