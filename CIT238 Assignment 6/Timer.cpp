#ifdef _WIN32
	#include <windows.h>
#elif __APPLE__
	#include <assert.h>
	#include <CoreServices/CoreServices.h>
	#include <mach/mach.h>
	#include <mach/mach_time.h>
	#include <unistd.h>
#endif

#include <iostream>

#include "Timer.h"

Timer::Timer()
{
	startTime = 0;
	timePassed = 0;

#ifdef _WIN32
	//This sets our secondsPerCount and mSecondsPerCount variables  
	//so that we can convert from Tics to seconds or milliseconds 
	uint64_t countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	secondsPerCount = 1.0 / (double)countsPerSec;
	mSecondsPerCount = secondsPerCount * 1000;
#elif __APPLE__
	mach_timebase_info(&timeInfo);
#endif
}

void Timer::Start(bool reset)
{
	if (reset)
		Reset();

#ifdef _WIN32
	//This just sets startTime to the current time
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
#elif __APPLE__
	startTime = mach_absolute_time();
#endif
}

void Timer::Stop()
{
#ifdef _WIN32
	//This sets currTime to the current time, then subtracts startTime 
	//from currTime to get the elapsed time since Start() was called.
	uint64_t currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	timePassed += currTime - startTime;
#elif __APPLE__
	timePassed += mach_absolute_time() - startTime;
#endif
}

void Timer::Reset()
{
	//This sets timePassed back to 0 assuming Start() and Stop() 
	//have been called to record some amount of elapsed time
	timePassed = 0;
}

uint64_t Timer::GetTicsElapsed()
{
	return timePassed;
}

double Timer::GetSecondsElapsed()
{
#ifdef _WIN32
	return timePassed * secondsPerCount;
#elif __APPLE__
	//Result will be in nanoseconds for mac, so convert to seconds.
	return (timePassed * (timeInfo.numer / timeInfo.denom)) / 1000.0 / 1000.0 / 1000.0;
#endif
}

double Timer::GetMillisecondsElapsed()
{
#ifdef _WIN32
	return timePassed * mSecondsPerCount;
#elif __APPLE__
	//Result will be in nanoseconds for mac, so convert to milliseconds.
	return (timePassed * (timeInfo.numer / timeInfo.denom)) / 1000.0 / 1000.0;
#endif
}

//This one is for using variables like Report(str); where str is a string variable.
void Timer::Report(const std::string& caption, int numTrialsToAverage)
{
	if (!caption.empty())
		std::cout << caption << ": ";

	std::cout << GetSecondsElapsed() / numTrialsToAverage
		<< "s, " << GetMillisecondsElapsed() / numTrialsToAverage
		<< "ms, " << GetTicsElapsed() / numTrialsToAverage << "t."
		<< (numTrialsToAverage > 1 ? " averaged over " + std::to_string(numTrialsToAverage) + " trials" : "")
		<< std::endl;
}