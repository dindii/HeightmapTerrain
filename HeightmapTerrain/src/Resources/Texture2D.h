#pragma once
#include <string>
#include <Rendering/Renderer.h>

namespace Height
{
	class Texture2D
	{
	public:
		Texture2D() : m_Handle(0), m_RawData(nullptr), m_Width(0), m_Height(0), m_ChannelsCount(0) {};
		Texture2D(const std::string& path, bool registerDataToGPU = true);
		~Texture2D();

		inline const uint8_t* GetData()      { return m_RawData; }
		inline uint32_t GetWidth()     const { return m_Width; }
		inline uint32_t GetHeight()    const { return m_Height; }
		inline uint32_t GetChannels()  const { return m_ChannelsCount; }

		void Bind(EMapType slot) const;

		void UploadGPUData();
		void UnloadCPUData();

	private:
		uint32_t m_Handle;
		uint8_t* m_RawData;
		uint32_t m_Width, m_Height;
		uint32_t m_ChannelsCount;
	};
}