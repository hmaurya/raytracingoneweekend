#pragma once

#include <iostream>

namespace rt
{

	template<typename T>
	class Vector3 
	{
	public:

		Vector3() = default;
		Vector3(T aX, T aY, T aZ) : m_e0(aX), m_e1(aY), m_e2(aZ) {}
		
		static Vector3 forward() { return Vector3(static_cast<T>(0), static_cast<T>(0), static_cast<T>(1)); }
		static Vector3 right() { return Vector3(static_cast<T>(1), static_cast<T>(0), static_cast<T>(0)); }
		static Vector3 up() { return Vector3(static_cast<T>(0), static_cast<T>(1), static_cast<T>(0)); }

		inline T x() const { return m_e0; }
		inline T y() const { return m_e1; }
		inline T z() const { return m_e2; }
		// TODO we can do a 
		inline T r() const { return m_e0; }

	private:
		T m_e0, m_e1, m_e2;


	};
}