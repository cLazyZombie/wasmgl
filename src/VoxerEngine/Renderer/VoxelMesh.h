#pragma once

#include "IVoxelMesh.h"
#include "VoxelVertex.h"

namespace VoxerEngine
{
	class VoxelMesh : public IVoxelMesh
	{
	private:
		vector<VoxelVertex> m_vertexes;
		vector<uint32_t> m_indexes;

        GLuint m_vbo = 0;
        GLuint m_ibo = 0;
		uint32_t m_vertexCount = 0;
		uint32_t m_indexCount = 0;

		bool m_built = false;

	public:
		VoxelMesh();
		virtual ~VoxelMesh();

		virtual uint32_t AddVertex(const VoxelVertex& vertex) override;
		virtual void AddTriangle(uint32_t index1, uint32_t index2, uint32_t index3) override;
		virtual void Build() override;
		virtual void BindBuffer() override;
		virtual void Render() override;

	private:
		uint32_t GetVertexCount() const;
		uint32_t GetTriangleCount() const;

		uint32_t GetVertexBufferSize() const;
		const VoxelVertex* GetVertexBufferPointer() const;

		uint32_t GetIndexBufferSize() const;
		const uint32_t* GetIndexBufferPointer() const;
	};
}