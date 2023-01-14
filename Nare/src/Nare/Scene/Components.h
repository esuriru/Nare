#pragma once

#include "Nare/Renderer/Mesh.h"

namespace Nare
{
    // TODO - Put all components inside this header file, since components are meant to be data-only, no logic.
    struct RenderMesh
    {
        Mesh mesh;
        
    };

	struct Transform
	{
		Transform() = default;
		Transform(const Vector3& pos)
			: position(pos) {};

        // Local 
		Vector3 position{};
		Quaternion rotation = Quaternion::identity;
		Vector3 scale = { 1, 1, 1 };
        Matrix4x4 localMatrix;

        // World
        Matrix4x4 worldMatrix;

        Transform* parent;
        std::vector<Transform*> children;
	};

    struct Light
    {
        enum LightType 
        {
            None = 0,
            Spot, Point, Directional
        };

        LightType type;
        Vector3 position;
        Vector3 direction;
        Vector4 colour;

        float power;

        float cos_cutoff;
        float cos_inner; 

        float constant;
        float linear;
        float quadratic;
    };
}