#pragma once
#include <stdint.h>
#include <vector>
#include <Math/vec3.h>
#include <Math/vec2.h>
#include <Math/vec4.h>
#include <Camera/Camera.h>
#include <Rendering/Renderable.h>

namespace Height
{

class Mesh;

	enum ERenderMode : uint8_t
	{
		BEGIN = 0,
		TRIANGLE = BEGIN,
		POINT,
		LINE,
		END
	};

	enum EMapType : uint8_t
	{
		BEGIN_MAP = 0,
		DIFFUSE_MAP = BEGIN_MAP,
		//specular
		//ambient occlusion
		//etc...
		END_MAP
	};

	class Renderer
	{
	public:
		static void Init();
		static void Clear(const bool ColorBuffer = true, const bool DepthBuffer = true);
		static void SetClearColor(const vec4& color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetWireframeMode(ERenderMode mode);
		static void Draw(Mesh* mesh, Camera* camera);

		static uint32_t GenResourceHandle();
		static uint32_t GenIndexHandle();

		static void BindTexture(uint32_t textureHandle, EMapType type);

		static void RegisterData(const RenderingHandles& handle, const std::vector<vec3>& vertexPositions, const std::vector<uint32_t>& indices, const std::vector<vec2>& texCoords);
		static uint32_t RegisterTextureResource(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels);
	};
}