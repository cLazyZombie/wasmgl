#pragma once

namespace VoxerEngine
{
	struct VoxelVertex
	{
		glm::vec3   Position;
		glm::vec3   Normal;
		glm::vec2   UV;

		inline VoxelVertex(glm::vec3& pos, const glm::vec3& nor, const glm::vec2& uv) : Position(pos), Normal(nor), UV(uv) {}
		inline VoxelVertex(float x, float y, float z) : Position(x, y, z), Normal(glm::vec3(0, 0, 1)), UV(0.0f, 0.0f) {}
		inline 	VoxelVertex() {}
	};
}