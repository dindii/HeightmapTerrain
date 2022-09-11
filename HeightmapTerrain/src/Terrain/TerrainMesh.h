#pragma once
#include "Resources/Mesh.h"
#include "Resources/Texture2D.h"

class string;

namespace Height
{
	class TerrainMesh : public Mesh
	{
	public:
		TerrainMesh(const std::string& heightMap, float scale, float offset);
		const Texture2D& GetTexture() { return m_Heightmap; }
	private:
		Texture2D m_Heightmap;
	};

}