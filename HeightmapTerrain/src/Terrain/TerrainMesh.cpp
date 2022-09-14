#include "TerrainMesh.h"
#include <string>
#include <chrono>

namespace Height
{
	TerrainMesh::TerrainMesh(const std::string& heightMap, float scale, float offset) : m_Heightmap(heightMap)
	{
		//Used to map pixel values to [0,1]
		float normalizedScale = scale / 256.0f;

		//We will be using the resolution of the image as the size of the terrain.
		int32_t height = m_Heightmap.GetHeight();
		int32_t width =  m_Heightmap.GetWidth();
		uint16_t channelsCount = m_Heightmap.GetChannels();

		const uint8_t* textureData = m_Heightmap.GetData();

		m_VertexPositions.reserve(height * width);

		//Since we have only 4 vertices per quad, for each vertex, we will generate 6 indices in order to make a quad with 2 triangles.
		m_Indices.reserve(height * width * 6);

		m_TextureCoord.reserve(height * width);
		
		m_Normal.reserve(height * width);
		m_Normal.resize(height * width);
		
		for (uint32_t y = 0; y < height; y++)
			for (uint32_t x = 0; x < width; x++)
			{
				//This way we can use a texture to cover all the terrain. Starting by 0.0f in its first vertex and going to ~1.0f in its last.
				float textureCoordX = (float)x / width;
				float textureCoordY = (float)y / width;

				m_TextureCoord.emplace_back(textureCoordX, textureCoordY);

				//Fetch pixel value respecting data channel stride
				const uint8_t* pixelData = textureData + (x + width * y) * channelsCount;
				uint8_t  pixelValue = *pixelData;

				//Vertex X and Z could be 0.0f, and the terrain would be plot in the position {0.0f, 0.0f} but we decrement a half of the terrain size, so we can let the middle of the terrain in the zero position.
				//This would get us negative values for the first half and positive for the second one. It is also better for visualization.
				float vertexX = -height / 2.0f + y;
				float vertexZ = -width / 2.0f + x;

				//Offset here is used so we can have below zero points on the terrain. This way we can have a more convincent looking terrain. Position 0 would become -offset and max position would become MAX-offset.
				float vertexY = (int)pixelValue * normalizedScale - offset;

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
			//Get all vertices of a triangle
			vec3 v0 = m_VertexPositions[m_Indices[v]];
			vec3 v1 = m_VertexPositions[m_Indices[v + 1]];
			vec3 v2 = m_VertexPositions[m_Indices[v + 2]];

			//Take the normal of a vertex of this triangle. Since all vertices are in the same plane, their normal are pretty much the same, so we don't need to make this for all
			//three vertices.
			vec3 n0 = vec3::Normalize(vec3::Cross(v1 - v0, v2 - v0));

			//If this vertex's normal is set, then, lets get this value.
			vec3 n0_old = m_Normal[m_Indices[v    ]];
			vec3 n1_old = m_Normal[m_Indices[v + 1]];
			vec3 n2_old = m_Normal[m_Indices[v + 2]];

			//We then get the halfway vector between the new normal and the old normal. This way we can interpolate all 8 triangles that share the same vertex.
			m_Normal[m_Indices[v    ]] = vec3::Normalize((n0_old + n0));
			m_Normal[m_Indices[v + 1]] = vec3::Normalize((n1_old + n0));
			m_Normal[m_Indices[v + 2]] = vec3::Normalize((n2_old + n0));
		}

		//Register all attributes to opengl and upload the data to the GPU.
		RegisterMeshData();

		//#NOTE: At this point, you can free all the member std::vectors. All data remains in the GPU right now, we will not use this data in system memory anymore.

		//Free texture byte array.
		m_Heightmap.UnloadCPUData();
	}
}