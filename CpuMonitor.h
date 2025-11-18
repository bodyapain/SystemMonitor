#pragma once
#include "ProcessMonitor.h"
#include <iostream>
#include <wil\resource.h>

class CpuMonitor : public ProcessMonitor<CpuMonitor>
{
	public:
	void onStart();
	void onStop();
	void onReport();
private:
	ULARGE_INTEGER m_lastIdleTime;
	ULARGE_INTEGER m_lastSystemTime;
	FILETIME idleTimePrev = {}, kernelTimePrev {}, userTimePrev = {};
};

