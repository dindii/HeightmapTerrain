#pragma once

namespace Height
{
	class DeltaTime
	{
	public:
		DeltaTime() : currentTime(0), previousTime(0), deltaTime(0.0f), secondsPerCount(0.0f) {};
		void Tick();

		operator float() { return deltaTime; }
		float Milliseconds() const { return deltaTime * 1000; }

	private:
		float currentTime;
		float previousTime;
		float deltaTime;
		float secondsPerCount;
	};
}