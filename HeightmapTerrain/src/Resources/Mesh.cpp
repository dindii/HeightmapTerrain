#include "Mesh.h"

namespace Height
{

	void Mesh::SetVertexPositionData(std::vector<vec3>&& vertexPosData) noexcept
	{
		 m_VertexPositions = vertexPosData; 
		 
		 UploadData(m_VertexPositions);
	}

}