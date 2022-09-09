#include "Renderable.h"
#include <Rendering/Renderer.h>
#include <vector>
#include <Math/vec3.h>

namespace Height
{
	Renderable::Renderable() : m_ObjectHandle(0)
	{
		m_ObjectHandle = Renderer::GenResourceHandle();
	}

	void Renderable::UploadData(const std::vector<vec3>& vertexPositions)
	{
		Renderer::RegisterData(m_ObjectHandle, vertexPositions);
	}

}