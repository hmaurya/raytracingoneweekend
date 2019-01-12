#pragma once

#include <vector>

#include "hitable.h"

namespace rt
{
	class Sphere : public Hitable
	{
	public:
		Sphere() = default;
		Sphere(Vector3f aCenter, float aRadius)
			: mCenter(aCenter)
			, mRadius(aRadius) {}

		Vector3f center() const {
			return mCenter;
		}

		float radius() const {
			return mRadius;
		}

		void setCenter(const Vector3f& aCenter) {
			mCenter = aCenter;
		}

		void setRadius(float aRadius) {
			mRadius = aRadius;
		}

		bool hit(const Ray& aRay, float t_min, float t_max, HitRecord& hitRecord) const;

		static bool hitSpheres(const Ray& aRay, 
			float t_min, 
			float t_max, 
			const std::vector<Hitable*>& aHitables, 
			HitRecord& aRecord);

	private:
		Vector3f mCenter;
		float mRadius;
	};
}