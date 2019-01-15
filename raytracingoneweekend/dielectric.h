#pragma once

#include "material.h"
#include "utilities.h"

namespace rt
{
	class Dielectric : public Material
	{
	public:
		Dielectric(float aRefIndex) : mRefIndex(aRefIndex) {}

		virtual bool scatter(const Ray& aRayIn, const HitRecord& aHitRecord, Vector3f& aAttenuation, Ray& aScattered) const override
		{
			Vector3f outwardNormal;
			Vector3f reflected = reflect(aRayIn.direction(), aHitRecord.normal);
			float ni_over_nt;
			aAttenuation = Vector3f(1.0f, 1.0f, 1.0f);
			Vector3f refracted;
			if (Vector3f::dot(aRayIn.direction(), aHitRecord.normal) > 0.0f) {
				outwardNormal = -aHitRecord.normal;
				ni_over_nt = mRefIndex;
			}
			else {
				outwardNormal = aHitRecord.normal;
				ni_over_nt = 1.0f / mRefIndex;
			}

			if (refract(aRayIn.direction(), outwardNormal, ni_over_nt, refracted)) {
				aScattered = Ray(aHitRecord.p, refracted);
			}
			else {
				aScattered = Ray(aHitRecord.p, reflected);
				return false;
			}
			return true;
		}

	private:
		float mRefIndex;
	};
}