#include "Texture2D.h"
#include <Util/HAssert.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>

namespace Height
{

	Texture2D::Texture2D(const std::string& path)
	{
		int32_t width = 0, height = 0;
		int32_t channelsCount = 0;

		uint8_t* data = stbi_load(path.c_str(), &width, &height, &channelsCount, 0);

		//#NOTE: In a real world scenario, we would not just fail the user and let this unsafe nullptr wandering. We would set this texture to the ID
		//of a default placeholder texture, so the user can also see that the texture is missing without needing to read the log.
		HT_ASSERT(data, "Failed to load texture!");

		m_RawData = data;
	}

	Texture2D::~Texture2D()
	{
		stbi_image_free(m_RawData);
	}

}