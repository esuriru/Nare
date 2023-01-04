#pragma once
#include "Vector4.h"

// TODO: Write regions

struct Quaternion
{
	float& x = data_.x; 
	float& y = data_.y;
	float& z = data_.z;
	float& w = data_.w;

	Quaternion(float x = 0.f, float y = 0.f, float z = 0.f, float w = 1.f);

	float Length() const;

	Quaternion& Normalize();

	Quaternion GetConjugate();

	Quaternion operator*(const Quaternion& rhs) const;

	static Quaternion Euler(Vector3 PYRdegrees);
	static Quaternion Euler(float pitch, float yaw, float roll);

private:
	Vector4 data_;
};




