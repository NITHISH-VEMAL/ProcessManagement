	/* DISK USAGE - percentage of computer storage in USE */



#include <winsock2.h>
#include <Ws2tcpip.h>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <psapi.h>
#include <iostream>
#include <string>
#include<WinBase.h>
#include <iphlpapi.h>
#include <Tcpestats.h>

using namespace std;




void findDiskUsage(DWORD processID)
{
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, processID);
	IO_COUNTERS sticCounter = { 0 };



	////////////////////////////////////////////////////////////////////////////////////////////////////////////
						GetProcessIoCounters(hProcess, &sticCounter);
			cout << "Disk usage : " << sticCounter.WriteTransferCount * 0.000000125 << "Mb" << endl << endl;
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////


}