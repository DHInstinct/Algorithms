#pragma once

#ifdef __APPLE__
	#include <mach/mach_time.h>
#endif

#include <string>

///A high precision timer class.
class Timer
{
public:	
	//Constructor
	Timer();

	//Start timing, or resume if Stop() was called before Reset()
	void Start(bool reset = true);

	//Stop timing. Does not reset.
	void Stop(); 

	//Reset the timer
	void Reset();  

	//Return how many tics (CPU clock cycles) have passed
	uint64_t GetTicsElapsed();

	//Return how many seconds have passed
	double GetSecondsElapsed();

	//Return how many millieseconds have passed
	double GetMillisecondsElapsed(); 

	//prints out how many seconds, ms, and tics it timed.
	void Report(const std::string& caption = "", int numTrialsToAverage = 1);

private:
	//uint64_t is the same as unsigned long long, or a non-negative really really big integer.
	uint64_t startTime;
	uint64_t timePassed;

#ifdef _WIN32
	double secondsPerCount;
	double mSecondsPerCount;
#elif __APPLE__
	mach_timebase_info_data_t timeInfo;
#endif
};