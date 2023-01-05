#pragma once

#include <Nare/NareMath.h>

namespace Nare
{
	struct Transform
	{
		Vector3 position{};
		Quaternion rotation = Quaternion::identity;
		Vector3 scale = { 1, 1, 1 };

		Transform() = default;
		Transform(const Vector3& pos)
			: position(pos) {};


	private:
		Transform* parent_;
		std::vector<Transform*> children_;
	};
}