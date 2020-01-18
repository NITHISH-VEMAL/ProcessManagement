/* pass the process ID and use shellExecute command to terminate*/










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




void Terminate(DWORD processID)
{

	HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);                       //  handle for each process
	
	if (NULL != tmpHandle)
	{
		//////////////////////////////////////////
		     TerminateProcess(tmpHandle, 0);                       //    terminate process
	   /////////////////////////////////////////
	}

	if (CloseHandle(tmpHandle)) { return; }

}
