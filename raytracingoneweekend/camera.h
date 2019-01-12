#pragma once

#include "Vector3.h"
#include "ray.h"

namespace rt {

	class Camera
	{
	public:

		Camera() {
			mLowerLeftCorner = Vector3f{ -2.0, -1.0, -1.0 };
			mHorizontal = Vector3f{ 4.0, 0.0, 0.0 };
			mVerticle = Vector3f{ 0.0, 2.0, 0.0 };
			mOrigin = Vector3f{ 0.0, 0.0, 0.0 };
		}

		Ray ray(float aU, float aV) {
			return Ray(mOrigin, (mLowerLeftCorner + aU * mHorizontal + aV * mVerticle) - mOrigin);
		}

	private:
		Vector3f mLowerLeftCorner;
		Vector3f mHorizontal;
		Vector3f mVerticle;
		Vector3f mOrigin;
	};

}