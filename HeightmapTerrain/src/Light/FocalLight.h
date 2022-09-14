#pragma once
#include <Math/vec3.h>

namespace Height
{
	class FocalLight
	{
	public:
		FocalLight(const vec3& position, const vec3& color);
		FocalLight() = default;

		void SetPosition(const vec3& pos) { m_Position = pos; }
		void AddPosition(const vec3& pos) { m_Position += pos; }

		bool SetColor(const vec3& color);
		inline vec3 GetPosition() const { return m_Position; }
		inline vec3 GetColor() const { return m_Color; }

	private:
		bool AssertColor(const vec3& color);

		vec3 m_Position, m_Color;
	};
}