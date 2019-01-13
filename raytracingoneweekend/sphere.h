#pragma once

#include <vector>

#include "hitable.h"
#include "material.h"

namespace rt
{
	class Sphere : public Hitable
	{
	public:
		Sphere() = default;
		Sphere(Vector3f aCenter, float aRadius, Material* aMaterial)
			: mCenter(aCenter)
			, mRadius(aRadius) 
			, mMaterial(aMaterial)
		{}

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

		bool hit(const Ray& aRay, float t_min, float t_max, HitRecord& hitRecord) const override;

		static bool hit(const Ray& aRay, 
			float t_min, 
			float t_max, 
			const std::vector<Hitable*>& aHitables, 
			HitRecord& aRecord);

	private:
		Vector3f mCenter;
		float mRadius;
		Material *mMaterial;
	};
}