#include "FocalLight.h"

namespace Height
{
		FocalLight::FocalLight(const vec3& position, const vec3& color) : m_Position(position)
		{
			SetColor(color);
		}

		bool FocalLight::SetColor(const vec3& color)
		{
			if (!AssertColor(color))
			{
				m_Color = color;
				return true;
			}

			std::cerr << "There's a pitch black or negative light, is this your intent? Skipping this one." << std::endl;
			return false;
		}

		bool FocalLight::AssertColor(const vec3& color)
		{
			return (color.r <= 0.0f && color.g <= 0.0f && color.b <= 0.0f);
		}
}