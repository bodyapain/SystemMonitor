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
	FILETIME currentidleTimePrev, currentkernelTimePrev, currentUserTimePrev;
	if (!(GetSystemTimes(&currentidleTimePrev, &currentkernelTimePrev, &currentUserTimePrev)))
	{
		THROW_LAST_ERROR();
	}
	ULARGE_INTEGER processTime, systemTime;
	auto toUInt64 = [](FILETIME ft) {
		return ((uint64_t)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
		};
	uint64_t idleDiff = toUInt64(currentidleTimePrev) - toUInt64(idleTimePrev);
	uint64_t kernelDiff = toUInt64(currentkernelTimePrev) - toUInt64(kernelTimePrev);
	uint64_t userDiff = toUInt64(currentUserTimePrev) - toUInt64(userTimePrev);

	idleTimePrev = currentidleTimePrev;
	kernelTimePrev = currentkernelTimePrev;
	userTimePrev = currentUserTimePrev;

	uint64_t total = kernelDiff + userDiff;
	std::cout <<  (total ? (1.0 - (float)idleDiff / total) * 100.0 : 0.0 )<< std::endl;
}
