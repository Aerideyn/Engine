#pragma once
namespace Services
{
	class Timer
	{
	public:
		Timer();
		~Timer();
	private:
		double offset = 0.0;
	public:
		double GetElapsed();
		double Reset();
	};
}
