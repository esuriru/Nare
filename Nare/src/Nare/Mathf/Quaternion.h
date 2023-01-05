#pragma once
#include "Vector4.h"

// TODO: Write regions
// TODO: Might make a macro to make it so that users can choose between (w, x, y, z) and (x, y, z, w)
// TODO: By default GLM store quaternion components with the x, y, z, w order. GLM_FORCE_QUAT_DATA_WXYZ allows switching the quaternion data storage to the w, x, y, z order."

struct Quaternion
{
	float& x = data_.x; 
	float& y = data_.y;
	float& z = data_.z;
	float& w = data_.w;

	Quaternion(float w = 1.f, float x = 0.f, float y = 0.f, float z = 0.f);

	float Length() const;

	Quaternion& Normalize();

	Quaternion GetConjugate();

	Quaternion operator*(const Quaternion& rhs) const;

	static Quaternion Euler(Vector3 PYRdegrees);
	static Quaternion Euler(float pitch, float yaw, float roll);

	static const Quaternion& identity;

private:
	Vector4 data_;
};




