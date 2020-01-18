

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

#include "terminate.h"
#include "printpname.h"
#include "memoryinfo.h"
#include "cpuUsage.h"
#include "diskUsage.h"

using namespace std;

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")

#define MALLOC(x) HeapAlloc(GetProcessHeap(), 0, (x))
#define FREE(x) HeapFree(GetProcessHeap(), 0, (x))




//CPU usage is number of processor used -done
//Memory usage is memory used in RAM -done
//Disk usage is memory used in ROM   = read+write
//Ntework usage is = send+receive

/*void start(DWORD processID) {

	SYSTEM_INFO sysInfo;
	FILETIME ftime, fsys, fuser;

	GetSystemInfo(&sysInfo);
	numProcessors = sysInfo.dwNumberOfProcessors; //find number of processor

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&lastCPU, &ftime, sizeof(FILETIME));


	////////////////////////////////////////////////////////////////
	self = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);   //
 ///////////////////////////////////////////////////////////////


	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&lastSysCPU, &fsys, sizeof(FILETIME));
	memcpy(&lastUserCPU, &fuser, sizeof(FILETIME));
}

double getCurrentValue() {
	FILETIME ftime, fsys, fuser;
	ULARGE_INTEGER now, sys, user;
	double percent;

	GetSystemTimeAsFileTime(&ftime);
	memcpy(&now, &ftime, sizeof(FILETIME));

	GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
	memcpy(&sys, &fsys, sizeof(FILETIME));
	memcpy(&user, &fuser, sizeof(FILETIME));
	percent = (sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart);
	percent /= (now.QuadPart - lastCPU.QuadPart);
	percent /= numProcessors;
	lastCPU = now;
	lastUserCPU = user;
	lastSysCPU = sys;

	return percent * 100;
}

/*void memoryInformation(DWORD processID)
{

	/* MEMORY USAGE */


	// get access for both phy and virtual mem and get phy mem of specified process

	/*HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS, TRUE, processID);   //open process

	MEMORYSTATUSEX memInfo;                             //information about current memory
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);

	/////////////////////////////////////////////////
	GlobalMemoryStatusEx(&memInfo);       //  Information of phy mem and virtual mem
////////////////////////////////////////////////


 //DWORDLONG totalVirtualMem = memInfo.ullTotalPageFile;     
	PROCESS_MEMORY_COUNTERS pmc;

	///////////////////////////////////////////////////////////////////
	GetProcessMemoryInfo(tmpHandle, &pmc, sizeof(pmc));        //  Retrieves information of specified process
/////////////////////////////////////////////////////////////////


	DWORDLONG totalPhysMem = memInfo.ullTotalPhys;
	SIZE_T physMemUsedByMe = pmc.WorkingSetSize;


	cout << "Memory used is " << physMemUsedByMe * 0.000000125 << "Mb" << endl <<endl;


	/* CPU USAGE */

	/////////////////////////////////////////////////
	//start(processID);             // function call
////////////////////////////////////////////////

	/*printf("CPU usage is %lf\n", getCurrentValue());


	/* DISK USAGE */


	/*HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, TRUE, processID);
	IO_COUNTERS sticCounter = { 0 };

	if (!GetProcessIoCounters(hProcess, &sticCounter))
	{
		cout << "invalid";
	}
	//cout<<"read : "<<sticCounter.ReadOperationCount;
	//cout << " write : " << sticCounter.WriteOperationCount<<endl;
	cout << "Disk usage : " << sticCounter.WriteTransferCount * 0.000000125 << "Mb" << endl;//+ sticCounter.WriteTransferCount<<endl;
	//cout << " write transfer : " << sticCounter.WriteTransferCount << endl;

	PMIB_TCPTABLE pTcpTable;
	DWORD dwSize = 0;
	DWORD dwRetVal = 0;

	char szLocalAddr[128];
	char szRemoteAddr[128];
	pTcpTable = (MIB_TCPTABLE*)MALLOC(sizeof(MIB_TCPTABLE));
	if (pTcpTable == NULL) {
		printf("Error allocating memory\n");

	}

	dwSize = sizeof(MIB_TCPTABLE);


	// Make an initial call to GetTcpTable to
	// get the necessary size into the dwSize variable
	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == ERROR_INSUFFICIENT_BUFFER)
	{
		FREE(pTcpTable);
		pTcpTable = (MIB_TCPTABLE*)MALLOC(dwSize);
		if (pTcpTable == NULL)
		{
			printf("Error allocating memory\n");
		}
	}


	// Make a second call to GetTcpTable to get
	// the actual data we require
	int i;


	if ((dwRetVal = GetTcpTable(pTcpTable, &dwSize, TRUE)) == NO_ERROR)
	{
		//printf("\tNumber of entries: %d\n", pTcpTable->dwNumEntries);
		for (i = 0; i < (int)pTcpTable->dwNumEntries; i++)
		{
			//printf("\n\tTCP[%d] State: %ld - ", i, pTcpTable->table[i].dwState);

			//printf("\tTCP[%d] Local Port: %d \n", i, ntohs((u_short)pTcpTable->table[i].dwLocalPort));

			//printf("\tTCP[%d] Remote Port: %d\n", i, ntohs((u_short)pTcpTable->table[i].dwRemotePort));

			MIB_TCPROW row;
			row.dwLocalAddr = pTcpTable->table[i].dwLocalAddr;
			row.dwLocalPort = pTcpTable->table[i].dwLocalPort;
			row.dwRemoteAddr = pTcpTable->table[i].dwRemoteAddr;
			row.dwRemotePort = pTcpTable->table[i].dwRemotePort;
			row.dwState = pTcpTable->table[i].dwState;
			void* processRow = &row;


			ULONG rosSize = 0, rodSize = 0;
			ULONG winStatus;
			PUCHAR ros = NULL, rod = NULL;
			//rodSize = sizeof(TCP_ESTATS_DATA_ROD_v0);



			PTCP_ESTATS_DATA_ROD_v0 dataRod = { 0 };
			rodSize = sizeof(TCP_ESTATS_DATA_ROD_v0);
			//PTCP_ESTATS_DATA_ROD_v0 dataRod = { 0 };

			if (rosSize != 0) {
				ros = (PUCHAR)malloc(rosSize);
				if (ros == NULL) {
					wprintf(L"\nOut of memory");
					return;
				}
				else
					memset(ros, 0, rosSize); // zero the buffer
			}
			if (rodSize != 0) {
				rod = (PUCHAR)malloc(rodSize);
				if (rod == NULL) {
					free(ros);
					wprintf(L"\nOut of memory");
					return;
				}
				else
					memset(rod, 0, rodSize); // zero the buffer
			}


			///////////////////////////////////////////////
			winStatus = GetPerTcpConnectionEStats((PMIB_TCPROW)& row, TcpConnectionEstatsData, NULL, 0, 0, ros, 0, rosSize, rod, 0, rodSize);
			//////////////////////////////////////////////



			/* IPHLPAPI_DLL_LINKAGE ULONG GetPerTcpConnectionEStats(
				 PMIB_TCPROW     Row,
				 TCP_ESTATS_TYPE EstatsType,
				 PUCHAR          Rw,
				 ULONG           RwVersion,
				 ULONG           RwSize,
				 PUCHAR          Ros,
				 ULONG           RosVersion,
				 ULONG           RosSize,
				 PUCHAR          Rod,
				 ULONG           RodVersion,
				 ULONG           RodSize
			 ); */



		/*	dataRod = (PTCP_ESTATS_DATA_ROD_v0)rod;
			//cout<<dataRod->DataBytesIn<<endl;
			cout << dataRod->DataBytesOut << endl << endl;
		}
	}*/



//}


int main(int argc, TCHAR * argv[])
{
	cout << " 1: view all process\n 2: To start a new process\n 3: To terminate a process from listed\n";

	while (1)
	{
		int getOption;
		cout << "\nChoose your option : ";
		cin >> getOption;

		switch (getOption)
		{


			// case 1 to view all process
		case 1:
		{

			DWORD aProcesses[1024], cbNeeded, cProcesses;
			unsigned int i;
			////////////////////////////////////////////////////////////////////
			if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))               //     to get all the process ID [ array, size, number of bytes ]
			///////////////////////////////////////////////////////////////////
			{
				return 1;
			}



			cProcesses = cbNeeded / sizeof(DWORD);   //to find no. of 



			for (i = 0; i < cProcesses; i++)
			{
				if (aProcesses[i] != 0)
				{
				  ///////////////////////////////////////////////////////
				     	
					PrintProcessNameAndID(aProcesses[i]);                             
				    memoryInformation(aProcesses[i]);
					start(aProcesses[i]);
					getCurrentValue();
					findDiskUsage(aProcesses[i]);

				//////////////////////////////////////////////////////


				}
			}

			break;
		}



		//case 2 to start new process
		case 2:
		{



			///////////////////////////////////////////////////////////////////
			string processName;
			cout << "Enter the process name : ";
			cin >> processName;
			std::wstring ws;                                                   // convert string to LPCWSTR
			ws.assign(processName.begin(), processName.end());
			LPWSTR pwst = &ws[0];
			LPCWSTR pcwstr = ws.c_str();
			///////////////////////////////////////////////////////////////////




			/////////////////////////////////////////////////////////////////////
			     ShellExecute(0, L"open", pcwstr, NULL, 0, SW_SHOW);                  //   to open the process  [ message, whatToDo, fileName, parameter, directory, how to open]
           ////////////////////////////////////////////////////////////////////

			break;

		}




		case 3:
		{


			cout << "Enter the process ID to be deleted : ";
			DWORD processID;
			cin >> processID;


			//////////////////////////////////////
			       Terminate(processID);             //   terminate process function
    	  //////////////////////////////////////


			break;


		}



		}


	}

	return 0;
}
