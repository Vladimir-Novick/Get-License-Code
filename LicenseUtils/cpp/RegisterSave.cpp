
////////////////////////////////////////////////////////////////////////////
//	Copyright 2000-2017 : Vladimir Novick    https://www.linkedin.com/in/vladimirnovick/  
//        
//             https://github.com/Vladimir-Novick/Get-License-Code
//
//    NO WARRANTIES ARE EXTENDED. USE AT YOUR OWN RISK. 
//
// To contact the author with suggestions or comments, use  :vlad.novick@gmail.com
//
////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"
#include <stdio.h>
#include "RegisterSave.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LONG RegOpenKeyExM(
  HKEY hKey,         // handle to open key
  LPCTSTR lpSubKey,  // subkey name
  DWORD ulOptions,   // reserved
  REGSAM samDesired, // security access mask
  PHKEY phkResult    // handle to open key
);



CRegisterSave::CRegisterSave()
{
  strcpy(UserKeyPatch,_T("Software\\Software by Vladimir Novick\\Edictionary"));
}

CRegisterSave::~CRegisterSave()
{

}




void CRegisterSave::AutoRun(BOOL flag)
{
		HKEY hkeyRun;
        LPTSTR lpCmdLine;
        const char s_cszDebugKey[] = _T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run");
		const char s_ValueName[] = _T("EDictionary");

	if (flag){
        lpCmdLine = GetCommandLine(); //this line necessary for _ATL_MIN_CRT         LPTSTR lpCmdLine;

//	    RegOpenKeyExM(HKEY_LOCAL_MACHINE,s_cszDebugKey,0,KEY_WRITE,&hkeyRun);
//		RegSetValueEx(hkeyRun,s_ValueName,0,REG_SZ,(const unsigned char *)lpCmdLine,strlen(lpCmdLine));
//      RegCloseKey(hkeyRun);
	} else
	{
//	    RegOpenKeyExM(HKEY_LOCAL_MACHINE,s_cszDebugKey,0,KEY_ALL_ACCESS,&hkeyRun);
//		RegDeleteValue(hkeyRun,s_ValueName);
//        RegCloseKey(hkeyRun);
	}
}



void CRegisterSave::UserKeyStore(char *key, long *value,unsigned long LenRead,Storage StoreFlag)
{
    char BufText[255];
		 BufText[0]=0;
	switch(StoreFlag)
	{
	case WRITE :
		{
		 sprintf(BufText,"%d",*value);
		 UserKeyStore(key,BufText,strlen(BufText),CRegisterSave::WRITE);
		}
	case READ :
		{
		 UserKeyStore(key,BufText,254,CRegisterSave::READ);
		 *value = atol(BufText); 
		}
	}

}


void CRegisterSave::UserKeyStore(char *key, char *value,unsigned long LenRead,Storage StoreFlag)
{
		HKEY hkeyRun;
		HKEY hkeyRun2;
		DWORD dwType;
        DWORD dwDisposition;


	switch(StoreFlag)
	{
	case READ :
		*value = 0;
	    RegOpenKeyExM(HKEY_CURRENT_USER,UserKeyPatch,0,KEY_READ,&hkeyRun);
		RegQueryValueEx(hkeyRun,key,NULL,&dwType,(unsigned char *)value,&LenRead);
        RegCloseKey(hkeyRun);

		break;
	case WRITE :
		{
	    RegOpenKeyExM(HKEY_CURRENT_USER,UserKeyPatch,0,KEY_WRITE,&hkeyRun);
		RegSetValueEx(hkeyRun,key,0,REG_SZ,(const unsigned char *)value,LenRead);
		RegFlushKey(hkeyRun);
        RegCloseKey(hkeyRun);
		}
		break;
	case DELETE :
	    RegOpenKeyExM(HKEY_CURRENT_USER,UserKeyPatch,0,KEY_ALL_ACCESS,&hkeyRun);
		RegDeleteValue(hkeyRun,key);
        RegCloseKey(hkeyRun);
		break;
	}
}
