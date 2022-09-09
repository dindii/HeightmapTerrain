#include "TerrainMesh.h"
#include <string>

//namespace Height
//{
//	TerrainMesh::TerrainMesh(const std::string& heightMap, float scale, float offset)
//	{
//		m_Heightmap = Texture2D::Load(heightMap, true);
//
//		float normalizedScale = scale / 256.0f;
//
//		int32_t height = m_Heightmap->GetHeight();
//		int32_t width  = m_Heightmap->GetWidth();
//		uint16_t channelsCount = m_Heightmap->GetChannels();
//
//		unsigned char* textureData = m_Heightmap->GetData();
//
//		for (uint32_t y = 0; y < height; y++)
//			for (uint32_t x = 0; x < width; x++)
//			{
//				uint8_t* pixelData = textureData + (x + width * y) * channelsCount;
//				uint8_t  pixelValue = *pixelData;
//			
//				float vertexX = -height / 2.0f + y;
//				float vertexY = (int)pixelValue * normalizedScale - offset;
//				float vertexZ = -width / 2.0f + x;
//
//				m_VertexPositions.emplace_back(vertexX, vertexY, vertexZ);
//			}
//
//		m_Heightmap->UnloadData();
//	}
//}