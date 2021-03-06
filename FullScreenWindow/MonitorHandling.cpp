#include "stdafx.h"
#include "MonitorHandling.h"

namespace Wrapper
{

	void MonitorHandling::getMonitors(std::vector<Monitor>* monList)
	{
		// Adding a placeholder for the primary monitor
		monList->push_back(Monitor());

		BOOL res = EnumDisplayMonitors(
			NULL,
			NULL,
			&(MonitorHandling::MonitorEnumProc),
			(LPARAM)&monList
			);

	}


	BOOL CALLBACK MonitorHandling::MonitorEnumProc(
		_In_  HMONITOR hMonitor,
		_In_  HDC hdcMonitor, // NULL because we passed NULL to EnumDisplayMonitors
		_In_  LPRECT lprcMonitor,
		_In_  LPARAM dwData // Not changed by EnumDisplayMonitors
		)
	{
		MONITORINFOEX monitorInfoEx;
		monitorInfoEx.cbSize = sizeof(MONITORINFOEX);

		BOOL res = GetMonitorInfo(hMonitor, &monitorInfoEx);

		if (res)
		{
			std::wstring name(monitorInfoEx.szDevice);
			bool isPrimary = monitorInfoEx.dwFlags & MONITORINFOF_PRIMARY;
			RECT rect = monitorInfoEx.rcMonitor;
			int left = rect.left,
				top = rect.top,
				right = rect.right,
				bottom = rect.bottom;

			Monitor mon(name, isPrimary, left, top, right, bottom);

			// Dereferencing the pointer to the pointer to the monitor list
			std::vector<Monitor>* monList = *((std::vector<Monitor>**)dwData);
			monList->push_back(mon);

			if (isPrimary)
			{
				monList->at(0) = mon;
			}

			//LOG(info) << ((isPrimary) ? "PRIMARY " : "") << "Monitor \"" << name.c_str() << "\" found, coordonates: [(" << left << ", " << top << "), (" << right << ", " << bottom << ")].";
		}
		else
		{
			LOG(fatal) << "Unable to fill in monitor info.";
		}

		return TRUE;
	}


};
