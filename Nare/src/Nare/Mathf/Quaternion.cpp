#include "Quaternion.h"
#include "Nare/Core/NareMath.h"
#include "Nare/Core/Core.h"

const Quaternion& Quaternion::identity = Quaternion(1.0f, 0, 0, 0);

/// <summary>
/// Quaternions are stored and initialised as (w, x, y, z);
/// </summary>
Quaternion::Quaternion(float w, float x, float y, float z)
	: w(w), x(x), y(y), z(z)
{
}


float Quaternion::Length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}

Quaternion& Quaternion::Normalize()
{
    const float l = Length();
    NR_CORE_ASSERT(Mathf::ApproximatelyZero(l), "Trying to normalize a quaternion with magnitude zero.")

    x /= l;
    y /= l;
    z /= l;
    w /= l;
	return *this;
}

Quaternion Quaternion::GetConjugate()
{
	return {-x, -y, -z, w};
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
	return {
		x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y,
		y * rhs.w + w * rhs.y + z * rhs.x - x * rhs.z,
		z * rhs.w + w * rhs.z + x * rhs.y - y * rhs.x,
		w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z
	};
}

/**
 * \brief Returns a rotation quaternion that rotates z degrees around the z axis, x degrees around the x axis,
 * and y degrees around the y axis; applied in that order.
 * \param PYRdegrees Pitch, yaw and roll in degrees.
 * \return The quaternion with euler angles
 */
Quaternion Quaternion::Euler(Vector3 PYRdegrees)
{
	// Convert to radians
	PYRdegrees *= Mathf::Deg2Rad;
	const float cy = Mathf::Cos(PYRdegrees.y * 0.5f);
	const float sy = Mathf::Sin(PYRdegrees.y * 0.5f);
	const float cp = Mathf::Cos(PYRdegrees.x * 0.5f);
	const float sp = Mathf::Sin(PYRdegrees.x * 0.5f);
	const float cr = Mathf::Cos(PYRdegrees.z * 0.5f);
	const float sr = Mathf::Sin(PYRdegrees.z * 0.5f);

	return
	{
		cy * sp * cr + sy * cp * sr,
		sy * cp * cr - cy * sp * sr,
		sy * sp * cr - cy * cp * sr,
		cy * cp * cr + sy * sp * sr
	};

}

Quaternion Quaternion::Euler(float pitch, float yaw, float roll)
{
	// Convert to radians
	pitch *= Mathf::Deg2Rad;
	yaw *= Mathf::Deg2Rad;
	roll *= Mathf::Deg2Rad;
	const float cy = Mathf::Cos(yaw * 0.5f);
	const float sy = Mathf::Sin(yaw * 0.5f);
	const float cp = Mathf::Cos(pitch * 0.5f);
	const float sp = Mathf::Sin(pitch * 0.5f);
	const float cr = Mathf::Cos(roll * 0.5f);
	const float sr = Mathf::Sin(roll * 0.5f);

	return
	{
		cy * sp * cr + sy * cp * sr,
		sy * cp * cr - cy * sp * sr,
		sy * sp * cr - cy * cp * sr,
		cy * cp * cr + sy * sp * sr
	};
}
