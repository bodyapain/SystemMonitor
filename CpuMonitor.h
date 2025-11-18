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
	FILETIME idleTimePrev = {}, kernelTimePrev {}, userTimePrev = {};
};

