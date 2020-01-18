

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
