#include "Renderable.h"
#include <Rendering/Renderer.h>
#include <vector>
#include <Math/vec3.h>
#include <Math/vec2.h>

namespace Height
{
	Renderable::Renderable()
	{
		m_Handles.vertexBufferHandle = Renderer::GenResourceHandle();
		m_Handles.indexBufferHandle  = Renderer::GenIndexHandle();
	}

	void Renderable::UploadData(const std::vector<vec3>& vertexPositions, const std::vector<uint32_t>& indices, const std::vector<vec2>& texCoords)
	{
		Renderer::RegisterData(m_Handles, vertexPositions, indices, texCoords);
	}

}