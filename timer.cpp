#include "timer.hpp"

namespace gamehacking::helper
{
	Timer::Timer(double period_in_ms) {
		QueryPerformanceCounter(&time_);
		QueryPerformanceCounter(&time_at_start_);
		period_in_ms_ = period_in_ms;
	}

	Timer::Timer(void) {
		QueryPerformanceCounter(&time_);
		QueryPerformanceCounter(&time_at_start_);
	}

	bool Timer::Tick(double* out) {
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		static LARGE_INTEGER frequency = { 0 };
		if (frequency.QuadPart == 0) {
			QueryPerformanceFrequency(&frequency);
		}

		double delta_ms = (double)(time.QuadPart - time_.QuadPart) / frequency.QuadPart * 1000.0;
		if (delta_ms > period_in_ms_) {
			time_ = time;
			return true;
		}

		if (out) {
			if (period_in_ms_ != 0) {
				*out = (delta_ms / period_in_ms_);
			}
		}
		return false;
	}

	double Timer::GetElapsedTime(void) { // in MS
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		static LARGE_INTEGER frequency = { 0 };
		if (frequency.QuadPart == 0) {
			QueryPerformanceFrequency(&frequency);
		}

		double delta_ms = (double)(time.QuadPart - time_.QuadPart) / frequency.QuadPart * 1000.0;
		return delta_ms;
	}

	double Timer::GetTotalElapsedTime(void) { // in MS
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		static LARGE_INTEGER frequency = { 0 };
		if (frequency.QuadPart == 0) {
			QueryPerformanceFrequency(&frequency);
		}

		double delta_ms = (double)(time.QuadPart - time_at_start_.QuadPart) / frequency.QuadPart * 1000.0;
		return delta_ms;
	}

	TimerWithFunctionAndData::TimerWithFunctionAndData(int period_in_ms, void (*function)(void*), void* data) : Timer(period_in_ms) {
			this->function = function;
			this->data = data;
	}

	bool TimerWithFunctionAndData::Tick(void) {
		bool return_value = Timer::Tick(nullptr);
		if (return_value)
			function(data);
		return return_value;
	}

	void Timer::Reset(void)
	{
		QueryPerformanceCounter(&time_);
		QueryPerformanceCounter(&time_at_start_);
	}

	double Timer::GetTimeDifference(LARGE_INTEGER start, LARGE_INTEGER end)
	{
		static LARGE_INTEGER frequency = { 0 };
		if (frequency.QuadPart == 0) {
			QueryPerformanceFrequency(&frequency);
		}
		return (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart * 1000.0;
	}
}