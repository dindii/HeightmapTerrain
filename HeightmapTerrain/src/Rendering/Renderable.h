#pragma once
#include <stdint.h>
#include <vector>
#include <Math/vec3.h>

namespace Height
{
	class Renderable
	{
	public:
		Renderable();
		inline uint32_t GetHandle() const { return m_ObjectHandle; }

	protected:
		void UploadData(const std::vector<vec3>& vertexPositions);

	private:
		uint32_t m_ObjectHandle;
	};
}