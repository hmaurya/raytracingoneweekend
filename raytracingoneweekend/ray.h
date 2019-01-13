#pragma once

#include "vector3.h"

namespace rt {

	class Ray
	{
	public:

		Ray() = default;
		Ray(const Vector3f& aOrigin, const Vector3f& aDirection)
			: m_Origin(aOrigin)
			, m_Direction(aDirection) {}

		Vector3f origin() const { return m_Origin; }
		Vector3f direction() const { return m_Direction; }

		Vector3f pointAtParameter(float t) const {
			return m_Origin + m_Direction * t;
		}

	private:
		Vector3f m_Origin;
		Vector3f m_Direction;
	};
}