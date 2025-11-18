#pragma once
#include <iostream>
#include <thread>
#include <wil/resource.h>
#include <wil/result.h>
template <typename Derived>

class ProcessMonitor {
	public:
	~ProcessMonitor() {
		stopMonitoring(); 
	}
	void startMonitoring() 
	{
		startMonitoringThread();
		static_cast<Derived*>(this)->onStart();
	}
	void stopMonitoring() 
	{
		stopMonitorigThread();
		static_cast<Derived*>(this)->onStop();
	}
	void getStatus() 
	{
		static_cast<Derived*>(this)->onReport();
	}
private:

	void startMonitoringThread() 
	{
		if (m_hMonitoringThread.joinable()) return;
		m_hMonitoringThread = std::jthread([this](std::stop_token st)
			{
				while (!st.stop_requested())
				{
					this->getStatus();
					std::chrono::milliseconds m_interval = std::chrono::seconds(1);
					auto wake = std::chrono::steady_clock::now() + m_interval;
					while (!st.stop_requested() && std::chrono::steady_clock::now() < wake) {
						std::this_thread::sleep_for(std::chrono::milliseconds(10));
					}
				}
			});
	}

	void stopMonitorigThread() 
	{
		if (m_hMonitoringThread.joinable())
		{
			m_hMonitoringThread.request_stop();
			m_hMonitoringThread.join();
			std::cout << "monitoring thread stopped" << std::endl;
		}
	}

	std::jthread m_hMonitoringThread;
};

