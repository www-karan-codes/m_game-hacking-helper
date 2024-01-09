#pragma once

#include <Windows.h>

namespace gamehacking::helper
{
	struct Timer {
		LARGE_INTEGER time_;
		int period_in_ms_ = 1000;

		Timer(int period_in_ms);

		Timer(void);

		bool Tick(double* out);

		double GetElapsedTime(void);
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