#include "TerrainMesh.h"
#include <string>
#include <chrono>

namespace Height
{
	TerrainMesh::TerrainMesh(const std::string& heightMap, float scale, float offset) : m_Heightmap(heightMap)
	{
		float normalizedScale = scale / 256.0f;

		int32_t height = m_Heightmap.GetHeight();
		int32_t width =  m_Heightmap.GetWidth();
		uint16_t channelsCount = m_Heightmap.GetChannels();

		const uint8_t* textureData = m_Heightmap.GetData();

		m_VertexPositions.reserve(height * width);
		m_Indices.reserve(height * width * 6);
		m_TextureCoord.reserve(height * width);

		for (uint32_t y = 0; y < height; y++)
			for (uint32_t x = 0; x < width; x++)
			{
				float textureCoordX = (float)x / width;
				float textureCoordY = (float)y / width;

				m_TextureCoord.emplace_back(textureCoordX, textureCoordY);

				const uint8_t* pixelData = textureData + (x + width * y) * channelsCount;
				uint8_t  pixelValue = *pixelData;

				float vertexX = -height / 2.0f + y;
				float vertexY = (int)pixelValue * normalizedScale - offset;
				float vertexZ = -width / 2.0f + x;

				m_VertexPositions.emplace_back(vertexX, vertexY, vertexZ);
			}

		for (int z = 1; z < height - 1; z++)
			for (int x = 0; x < width - 1; x++)
			{
				uint32_t top = z * width + x;
				uint32_t bottom = (z - 1) * width + x;

				m_Indices.push_back(top);
				m_Indices.push_back(bottom);
				m_Indices.push_back(top + 1);

				m_Indices.push_back(top + 1);
				m_Indices.push_back(bottom);
				m_Indices.push_back(bottom + 1);
			}

		RegisterMeshData();

		m_Heightmap.UnloadCPUData();
	}
}