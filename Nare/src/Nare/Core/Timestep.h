#pragma once

namespace Nare
{
	// TODO: Might be more worth to make this a typedef instead, but good for readability.
	class Timestep
	{
	public:
		Timestep(float time = 0.0f) : time_(time) {};

		inline operator float() const { return time_; };

		inline float GetSeconds() const 
		{
			return time_;
		}

		inline float GetMilliseconds() const
		{
			return time_ * 1000.f;
		}
	private:
		float time_;
	};
}