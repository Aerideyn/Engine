#include "BoundingBox.h"
#include "BoundingSphere.h"
#include "BoundingFrustum.h"

BoundingVolume::BoundingBox::BoundingBox()
{
	min = glm::dvec3();
	max = glm::dvec3();
}

BoundingVolume::BoundingBox::BoundingBox(glm::dvec3 Min, glm::dvec3 Max)
{
	min = Min;
	max = Max;
}


BoundingVolume::BoundingBox::~BoundingBox()
{

}

bool BoundingVolume::BoundingBox::IntersectsBoundingBox(const BoundingVolume::BoundingBox& box)
{
	if (min.x <= box.max.x && max.x >= box.min.x)
	{
		if (min.x <= box.max.y && max.y >= box.min.y)
		{
			if (min.x <= box.max.z && max.z >= box.min.z)
				return true;
		}
	}
	return false;
}

bool BoundingVolume::BoundingBox::IntersectsBoundingFrustum(const BoundingVolume::BoundingFrustum& frustum)
{
	return true;
}

bool BoundingVolume::BoundingBox::IntersectsBoundingSphere(const BoundingVolume::BoundingSphere& sphere)
{
	double dmin = 0;

	if (sphere.centre.x < min.x) {
		dmin += pow(sphere.centre.x - min.x, 2);
	}
	else if (sphere.centre.x > max.x) {
		dmin += pow(sphere.centre.x - max.x, 2);
	}

	if (sphere.centre.y < min.y) {
		dmin += pow(sphere.centre.y - min.y, 2);
	}
	else if (sphere.centre.y > max.y) {
		dmin += pow(sphere.centre.y - max.y, 2);
	}

	if (sphere.centre.z < min.z) {
		dmin += pow(sphere.centre.z - min.z, 2);
	}
	else if (sphere.centre.z > max.z) {
		dmin += pow(sphere.centre.z - max.z, 2);
	}

	return dmin <= pow(sphere.radius, 2);
}

bool BoundingVolume::BoundingBox::ContainsPoint(glm::dvec3 point)
{
	return (point.x >= min.x && point.x <= max.x && point.y >= min.y && point.y <= max.y && point.z >= min.z && point.z <= max.z);
}