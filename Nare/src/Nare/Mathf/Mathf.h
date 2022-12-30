#pragma once

#include <limits>
/**
 * \brief Math namespace for floating-point math utility
 */
namespace Mathf
{
	/**
	 * \brief The magic number of Pi.
	 */
	constexpr float PI = 3.14159265358979323846f;

	/**
	 * \brief Degree to radian conversion constant.
	 */
	constexpr float Deg2Rad = (PI * 2) / 360;

	/**
	 * \brief Radian to degree conversion constant.
	 */
	constexpr float Rad2Deg = 360 / (PI * 2);

	/**
	 * \brief Tiny floating point value
	 */
	constexpr float Epsilon = std::numeric_limits<float>::epsilon();

	/**
	 * \brief Check if a float is approximately equal to the other float.
	 * \param a Float value 1
	 * \param b Float value 2
	 * \return Result (true or false)
	 */
	inline constexpr bool Approximately(const float a, const float b)
	{
		return a >= b - Epsilon && a <= b + Epsilon;
	}

	/**
	 * \brief Check if a float is approximately equal to zero.
	 * \param a Value to check
	 * \return Result (true or false)
	 */
	inline constexpr bool ApproximatelyZero(const float a)
	{
		return a <= Epsilon && -a <= Epsilon;
	}

}
