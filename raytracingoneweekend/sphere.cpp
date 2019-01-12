#include "pch.h"
#include "sphere.h"

namespace rt {

	bool Sphere::hit(const Ray& aRay, float t_min, float t_max, HitRecord& hitRecord) const
	{
		Vector3f oc = aRay.origin() - mCenter;
		float a = Vector3f::dot(aRay.direction(), aRay.direction());
		float b = 2.0f * Vector3f::dot(aRay.direction(), oc);
		float c = Vector3f::dot(oc, oc) - mRadius * mRadius;

		float discriminant = b * b - 4 * a * c;

		if (discriminant > 0.f) {
			float temp = (-b - sqrtf(discriminant)) / (2.0f * a);
			if (temp < t_max && temp > t_min) {
				hitRecord.t = temp;
				hitRecord.p = aRay.pointAtParameter(temp);
				hitRecord.normal = (hitRecord.p - mCenter) / mRadius;
				return true;
			}

			temp = (-b + sqrtf(discriminant)) / (2.0f * a);
			if (temp < t_max && temp > t_min) {
				hitRecord.t = temp;
				hitRecord.p = aRay.pointAtParameter(temp);
				hitRecord.normal = (hitRecord.p - mCenter) / mRadius;
				return true;
			}
		}

		return false;
	}

	bool Sphere::hitSpheres(const Ray & aRay, 
		float t_min, 
		float t_max, 
		const std::vector<Hitable*>& aHitables, 
		HitRecord & aRecord)
	{
		float nearest = std::numeric_limits<float>::max();
		bool hitAnything = false;

		for (size_t i = 0; i < aHitables.size(); ++i) {
			HitRecord record;
			if (aHitables[i]->hit(aRay, 0.0f, nearest, record)) {
				hitAnything = true;
				if (record.t < nearest) {
					nearest = record.t;
					aRecord = record;
				}
			}
		}
		return hitAnything;
	}


}
