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
		
		m_Normal.reserve(height * width);
		m_Normal.resize(height * width);
		
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

		for (int y = 0; y < height - 1; y++)
			for (int x = 0; x < width - 1; x++)
			{
				uint32_t top = x + width * (y + 1);
				uint32_t bottom = x + width * y;

				//Set indices in a counter-clock wise fashion so OpenGL can recognize front face vertices.
				m_Indices.push_back(bottom);
				m_Indices.push_back(top + 1);
				m_Indices.push_back(top);

				m_Indices.push_back(bottom);
				m_Indices.push_back(bottom + 1);
				m_Indices.push_back(top + 1);

			}

		for (int v = 0; v < m_Indices.size(); v += 3)
		{
			vec3 v0 = m_VertexPositions[m_Indices[v]];
			vec3 v1 = m_VertexPositions[m_Indices[v + 1]];
			vec3 v2 = m_VertexPositions[m_Indices[v + 2]];


			vec3 n0 = vec3::Normalize(vec3::Cross(v1 - v0, v2 - v0));

			vec3 n0_old = m_Normal[m_Indices[v]];
			vec3 n1_old = m_Normal[m_Indices[v + 1]];
			vec3 n2_old = m_Normal[m_Indices[v + 2]];

			m_Normal[m_Indices[v]] = vec3::Normalize((n0_old + n0));
			m_Normal[m_Indices[v + 1]] = vec3::Normalize((n1_old + n0));
			m_Normal[m_Indices[v + 2]] = vec3::Normalize((n2_old + n0));
		}


		RegisterMeshData();

		m_Heightmap.UnloadCPUData();
	}
}