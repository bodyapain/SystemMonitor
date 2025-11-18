#include <iostream>
#include "CpuMonitor.h"
int main()
{
    
    CpuMonitor cpuMonitor;
    cpuMonitor.startMonitoring();
    Sleep(100000);
    cpuMonitor.stopMonitoring();
}

