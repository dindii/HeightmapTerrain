#pragma once
#include <stdint.h>
#include <vector>
#include <Math/vec3.h>
#include <Math/vec2.h>

namespace Height
{
	struct RenderingHandles
	{
		uint32_t vertexBufferHandle = 0;
		uint32_t indexBufferHandle = 0;
	};

	class Renderable
	{
	public:
		Renderable();
		inline RenderingHandles GetRenderingHandles() const { return m_Handles; }
	protected:
		void UploadData(const std::vector<vec3>& vertexPositions, const std::vector<uint32_t>& indices, const std::vector<vec2>& texCoords);

	private:
		RenderingHandles m_Handles;
	};
}