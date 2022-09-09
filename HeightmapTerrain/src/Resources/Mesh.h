#pragma once
#include <Rendering/Renderable.h>
#include <Visual/Material.h>

namespace Height
{
	class Mesh : public Renderable
	{
	public:
		//Usually we have a lot of constructors, but in this case we don't need to expand it yet.
		 Mesh() = default;
		~Mesh() = default;

		inline uint32_t GetVertexCount() const { return (uint32_t)m_VertexPositions.size(); }

		//When we are not loading a mesh straight away from the constructor (with a path, maybe), we may want to create a Mesh to set it's data later.
		void SetVertexPositionData(std::vector<vec3>&& vertexPosData) noexcept;
		Material* GetMaterial() { return m_Material; }
		void AttachMaterial(Material* mat) { m_Material = mat; }
	private:
		std::vector<uint32_t> m_Indices;
		std::vector<vec3>     m_VertexPositions;

		Material* m_Material;
	};
}