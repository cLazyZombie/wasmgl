#pragma once

#include "Math/Vector3.h"
#include "Math/Float2.h"

namespace VoxerEngine
{
	struct VoxelVertex
	{
		Vector3   	Position;
		Vector3   	Normal;
		Float2		UV;

		inline VoxelVertex(Vector3& pos, const Vector3& nor, const Float2& uv) : Position(pos), Normal(nor), UV(uv) {}
		inline VoxelVertex(float x, float y, float z) : Position(x, y, z), Normal(Vector3(0, 0, 1)), UV(0.0f, 0.0f) {}
		inline 	VoxelVertex() {}
	};
}