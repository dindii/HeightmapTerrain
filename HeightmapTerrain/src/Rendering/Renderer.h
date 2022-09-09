#pragma once
#include <stdint.h>
#include <vector>
#include <Math/vec3.h>
#include <Math/vec4.h>
#include <Camera/Camera.h>

namespace Height
{

class Mesh;

	class Renderer
	{
	public:
		static void Init();
		static void Clear(const bool ColorBuffer = true, const bool DepthBuffer = true);
		static void SetClearColor(const vec4& color);
		static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height);
		static void SetWireframeMode(bool cond);
		static void Draw(Mesh* mesh, Camera* camera);

		static uint32_t GenResourceHandle();
		static void RegisterData(const uint32_t objectHandleToUploadData, const std::vector<vec3>& vertexPositions);
	};
}