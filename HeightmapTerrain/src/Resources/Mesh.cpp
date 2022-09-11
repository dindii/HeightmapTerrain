#include "Mesh.h"

namespace Height
{

	void Mesh::SetVertexPositionData(std::vector<vec3>&& vertexPosData) noexcept
	{
		 m_VertexPositions = vertexPosData; 
	}


	void Mesh::RegisterMeshData()
	{
		UploadData(m_VertexPositions, m_Indices, m_TextureCoord);
	}

}