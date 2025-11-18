#include "CpuMonitor.h"
#include <windows.h>
#include <chrono>
void CpuMonitor::onStart()
{
	std::cout << "CPU Monitoring started" << std::endl;
}

void CpuMonitor::onStop()
{
	std::cout << "CPU Monitoring stoped" << std::endl;
}

void CpuMonitor::onReport()
{
	FILETIME currentIdleTime, currentKernelTime, currentUserTime;
	if (!(GetSystemTimes(&currentIdleTime, &currentKernelTime, &currentUserTime)))
	{
		THROW_LAST_ERROR();
	}
	ULARGE_INTEGER processTime, systemTime;
	auto toUInt64 = [](FILETIME ft) {
		return ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
		};
	uint64_t idleDiff = toUInt64(currentIdleTime) - toUInt64(idleTimePrev);
	uint64_t kernelDiff = toUInt64(currentKernelTime) - toUInt64(kernelTimePrev);
	uint64_t userDiff = toUInt64(currentUserTime) - toUInt64(userTimePrev);

	idleTimePrev = currentIdleTime;
	kernelTimePrev = currentKernelTime;
	userTimePrev = currentUserTime;

	uint64_t total = kernelDiff + userDiff;
	std::cout <<  (total ? (1.0 - (float)idleDiff / total) * 100.0 : 0.0 )<< std::endl;
}
