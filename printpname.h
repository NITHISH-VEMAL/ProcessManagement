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


void PrintProcessNameAndID(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");  //enter as unknown for all process initially


  //////////////////////////////////////////////////////////////////////////////////////////////////
	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, TRUE , processID);      // provide an abstraction of a resource [ needed , inherit handle , id]
  /////////////////////////////////////////////////////////////////////////////////////////////////


	if (NULL != hProcess)
	{
		HMODULE hMod;
		DWORD cbNeeded;

		///////////////////////////////////////////////////////////////////////////////
		   if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded)) {}                  // handle for each module in the specified process
	   //////////////////////////////////////////////////////////////////////////////

		{


		 /////////////////////////////////////////////////////////////////////////////////////////////////
			GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));             //   get process name and store in szprocessname
		////////////////////////////////////////////////////////////////////////////////////////////////


		}
	}

	_tprintf(TEXT("%s  (PID: %u)\n"), szProcessName, processID);

	if (CloseHandle(hProcess))
	{
		return;
	}
}
