#include "Texture2D.h"
#include <Util/HAssert.h>
#include <Rendering/Renderer.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>

namespace Height
{

	Texture2D::Texture2D(const std::string& path, bool registerDataToGPU) : m_Handle(0), m_RawData(nullptr), m_Width(0), m_Height(0), m_ChannelsCount(0)
	{
		int32_t width = 0, height = 0;
		int32_t channelsCount = 0;

		uint8_t* data = stbi_load(path.c_str(), &width, &height, &channelsCount, 0);

		//#NOTE: In a real world scenario, we would not just fail the user and let this unsafe nullptr wandering. We would set this texture to the ID
		//of a default placeholder texture, so the user can also see that the texture is missing without needing to read the log.
		HT_ASSERT(data, "Failed to load texture!");

		m_Width = width;
		m_Height = height;
		m_ChannelsCount = channelsCount;

		m_RawData = data;

		if (registerDataToGPU)
			UploadGPUData();

		m_Path = path;
	}

	Texture2D::~Texture2D()
	{
		//We may want to free this data before. But in case we don't free it, check first and free.
		if(m_RawData)
			stbi_image_free(m_RawData);
	}

	void Texture2D::Bind(EMapType slot) const
	{
		Renderer::BindTexture(m_Handle, slot);
	}

	void Texture2D::UploadGPUData()
	{
		m_Handle = Renderer::RegisterTextureResource(m_RawData, m_Width, m_Height, m_ChannelsCount);
	}

	void Texture2D::UnloadCPUData()
	{
		stbi_image_free(m_RawData);
		m_RawData = nullptr;
	}
}