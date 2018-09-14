#include "stdafx.h"
#include "VoxelMesh.h"

namespace VoxerEngine
{
	VoxelMesh::VoxelMesh()
	{
	}

	VoxelMesh::~VoxelMesh()
	{
        if (m_vbo)
        {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }

        if (m_ibo)
        {
            glDeleteBuffers(1, &m_ibo);
            m_ibo = 0;
        }
	}

	uint32_t VoxelMesh::AddVertex(const VoxelVertex& vertex)
	{
		assert(m_built == false);

		uint32_t size = (uint32_t)(m_vertexes.size());
		m_vertexes.push_back(vertex);

		++m_vertexCount;
		
		return size;
	}

	void VoxelMesh::AddTriangle(uint32_t index1, uint32_t index2, uint32_t index3)
	{
		assert(m_built == false);

		m_indexes.push_back(index1);
		m_indexes.push_back(index2);
		m_indexes.push_back(index3);

		m_indexCount += 3;
	}

	void VoxelMesh::Build()
	{
		assert(m_built == false);

		// build VB
		if (m_vertexCount > 0)
		{
            glGenBuffers(1, &m_vbo);
            assert(m_vbo != 0);

            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
            assert(glGetError() == 0);

            glBufferData(GL_ARRAY_BUFFER, GetVertexBufferSize(), GetVertexBufferPointer(), GL_STATIC_DRAW);
            assert(glGetError() == 0);
		}

		// build IB
		if (m_indexCount > 0)
		{
            glGenBuffers(1, &m_ibo);
            assert(m_ibo != 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
            assert(glGetError() == 0);

            glBufferData(GL_ELEMENT_ARRAY_BUFFER, GetIndexBufferSize(), GetIndexBufferPointer(), GL_STATIC_DRAW);
            assert(glGetError() == 0);
		}

		// remove allocated vectors
		vector<VoxelVertex> vb;
		m_vertexes.swap(vb);

		vector<uint32_t> ib;
		m_indexes.swap(ib);
		m_built = true;
	}

	uint32_t VoxelMesh::GetVertexCount() const
	{
		return m_vertexCount;
	}

	uint32_t VoxelMesh::GetTriangleCount() const
	{
		return m_indexCount / 3;
	}

	uint32_t VoxelMesh::GetVertexBufferSize() const
	{
		return m_vertexCount * sizeof(VoxelVertex);
	}

	const VoxelVertex* VoxelMesh::GetVertexBufferPointer() const
	{
		return &(m_vertexes[0]);
	}

	uint32_t VoxelMesh::GetIndexBufferSize() const
	{
		return m_indexCount * sizeof(uint32_t);
	}

	const uint32_t* VoxelMesh::GetIndexBufferPointer() const
	{
		return &(m_indexes[0]);
	}

	void VoxelMesh::BindBuffer()
	{
		// bind vbo
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        assert(glGetError() == 0);

		// pos
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), 0);

		// normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), (const GLvoid *)(3 * sizeof(GLfloat)));

		// uv
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VoxelMesh), (const GLvoid *)(6 * sizeof(GLfloat)));

		// bind ibo
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
        assert(glGetError() == 0);
	}

	void VoxelMesh::Render()
	{
        glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, (void*)0);   
        assert(glGetError() == 0);
	}
}