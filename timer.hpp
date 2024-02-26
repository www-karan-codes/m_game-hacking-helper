#pragma once

#include <Windows.h>

namespace gamehacking::helper
{
	struct Timer {
		LARGE_INTEGER time_, time_at_start_;
		double period_in_ms_ = 1000;

		Timer(double period_in_ms);

		Timer(void);

		bool Tick(double* out);

		double GetElapsedTime(void);

		double GetTotalElapsedTime(void);

		void Reset(void);

		static double GetTimeDifference(LARGE_INTEGER start, LARGE_INTEGER end);
	};

	struct TimerWithFunctionAndData : public Timer {
	private:
		void* data = NULL;
		void (*function)(void*) = NULL;

	public:
		TimerWithFunctionAndData(int period_in_ms, void (*function)(void*), void* data);

		bool Tick(void);
	};
}