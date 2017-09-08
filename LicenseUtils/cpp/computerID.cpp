
///////////////////////////////////////////////////////////////////////////////////////////
//
//	Copyright 2000-2017 : Vladimir Novick    https://www.linkedin.com/in/vladimirnovick/  
//        
//             https://github.com/Vladimir-Novick/Get-License-Code
//
//    NO WARRANTIES ARE EXTENDED. USE AT YOUR OWN RISK. 
//
// To contact the author with suggestions or comments, use  :vlad.novick@gmail.com
//
////////////////////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"

#include "computerID.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const char * EncryptionKeys[NUM_ENCRYPTION_KEYS] = {
					 "75634298564129465734527745620576301569458788452369544213657563429856412946573452774562057630156945878845236954421365",
					 "57630156945878845236954421365512020021465763015694587883075763015694587884523695442136551202002146576301569458788307",
					 "46210326987462531251202002146587884523695442134656321231014621032698746253125120200214658788452369544213465632123101",
					 "88756694123265601246575458562258145789632560240021587410478875669412326560124657545856225814578963256024002158741047",
					 "25814578963254656321231012547763015694587884523695442163212581457896325465632123101254776301569458788452369544216321",
					 "12658457845612360240021587410695442136551202002146576231581265845784561236024002158741069544213655120200214657623158",
					 "45025468112684455126884589412302248653947226842823183218954502546811268445512688458941230224865394722684282318321895",
					 "02187463265698741203256987451269587456985264426000215845690218746326569874120325698745126958745698526442600021584569",
					 "14785265932145212541236547856952325412587896520123102102251478526593214521254123654785695232541258789652012310210225",
					 "45465845789210232145026982457952368412036589452032587151024546584578921023214502698245795236841203658945203258715102",
					 "01254789652314585239871258302159362154668765412015408949840125478965231458523987125830215936215466876541201540894984",
					 "10253698702529871325823854158522657472211680235965422697821025369870252987132582385415852265747221168023596542269782"

					};



static BYTE randomSeed[256] = {
	113, 21,232, 18,113, 92, 63,157,124,193,166,197,126, 56,229,229,
		156,162, 54, 17,230, 89,189, 87,169,  0, 81,204,  8, 70,203,225,
		160, 59,167,189,100,157, 84, 11,  7,130, 29, 51, 32, 45,135,237,
		139, 33, 17,221, 24, 50, 89, 74, 21,205,191,242, 84, 53,  3,230,
		231,118, 15, 15,107,  4, 21, 34,  3,156, 57, 66, 93,255,191,  3,
		85,135,205,200,185,204, 52, 37, 35, 24, 68,185,201, 10,224,234,
		7,120,201,115,216,103, 57,255, 93,110, 42,249, 68, 14, 29, 55,
		128, 84, 37,152,221,137, 39, 11,252, 50,144, 35,178,190, 43,162,
		103,249,109,  8,235, 33,158,111,252,205,169, 54, 10, 20,221,201,
		178,224, 89,184,182, 65,201, 10, 60,  6,191,174, 79, 98, 26,160,
		252, 51, 63, 79,  6,102,123,173, 49,  3,110,233, 90,158,228,210,
		209,237, 30, 95, 28,179,204,220, 72,163, 77,166,192, 98,165, 25,
		145,162, 91,212, 41,230,110,  6,107,187,127, 38, 82, 98, 30, 67,
		225, 80,208,134, 60,250,153, 87,148, 60, 66,165, 72, 29,165, 82,
		211,207,  0,177,206, 13,  6, 14, 92,248, 60,201,132, 95, 35,215,
		118,177,121,180, 27, 83,131, 26, 39, 46, 12, 79, 51, 86, 3, 202};

ComputerID::ComputerID()
{

}

ComputerID::~ComputerID()
{

}



bool ComputerID::ValidCheckSum(char * s)
{
    if (s == NULL )
        return false;
    if (strlen(s)  == 0 )
        return false;


    char cs[CSLENGTH+1]="";
	//first read the last two bytes into a character array and reverse them
	//then get their hex value
    for (int i=0;i<CSLENGTH;i++)
        cs[i]=s[strlen(s)-i -1];
	cs[CSLENGTH]='\0';

    char *endP = NULL;
    int checkSum = strtol(cs,&endP,16);

    int sum=0;
	int maxlenp= strlen(s)-CSLENGTH;
    for (i=0;i < maxlenp ;i++)
		if (s[i] != '-')
			sum += s[i];
    if ((sum % 256) == checkSum)
        return true;
    else
        return false;

}

void ComputerID::AddCheckSum(char * s)
{
	char temp[256];
   int sum=0;
   for (int i=0;i < strlen(s);i++)
		if (s[i] != '-')
			sum += s[i];
   //now take the sum and mod by 256 and store it as hex
   int cs = sum % 256;
   char csString[2]="";
   sprintf(csString, "%02X", cs);
   //now flip the two bytes and return them in the opposite order
   strcpy(temp,s);
   strcat(temp,csString);
   strcpy(s,temp);
   return; 
}



void ComputerID::SwapCheckSum (char * License)
{
	int len = strlen(License);
	int mid_index = len / 2;
	if (License[mid_index] == '-')
		mid_index++;

	char temp[2];
	for (int i=0; i < 2; i++)
	{
		temp[i] = License[mid_index+i];
		License[mid_index+i] = License[len-2+i];
	}
	for (i=0; i < 2; i++)
		License[len-2+i] = temp[i];

}

void ComputerID::DecryptEncrypt(char * inputString, int operation, int random_key)
{
   CString EncryptionKey = EncryptionKeys[random_key];

	int totalLen = strlen(inputString);
    CString outString (' ', totalLen); //create an empty string

    char c;
    for (int i=0; i < totalLen;i++)
    {
		  char base_char;
		  int base_mod;
		  if (isdigit(inputString[i]))
		  {
			  base_mod = 10;
			  base_char = '0';
		  }
		  else
		  {
			  base_mod=26;
			  if (isupper(inputString[i]))
				  base_char = 'A';
			  else
				  base_char = 'a';
		  }
      if (operation == ENCRYPT)
      {
			  c = ((inputString[i]-base_char) + (EncryptionKey[i]-'0')) % base_mod + base_char;
      }
      else //decrypt
      {
			  c = (inputString[i]-base_char) - (EncryptionKey[i]-'0') + base_char;
		  
        short diff = inputString[i] - (EncryptionKey[i]-'0');
        if ((inputString[i] < EncryptionKey[i]) ||
        // Kostia - attempt to fix bug in decryption 
        //when '9' < (inputString[i] - (EncryptionKey[i]-'0')) < 'A' 
          ('9' < diff && diff < 'A') || ('Z' < diff && diff < 'a'))
              c +=  base_mod;     
		  }
      outString.SetAt(i,c);
    }
    strcpy(inputString,outString);
}


void  ComputerID::GetComuterID(char * szNUM)  
{
  
  char temp1[255];
  char temp2[255];
  char szString[255];
  long cID;
  GetIDByHD(cID);
  sprintf(szString,"%d",cID);

  char m_sz256String[256];
  if (!szString)
    return;
  
UINT i;     

  for (i = 0; i < strlen(szString); i += 2)
  {
    
    char hi, low;
    hi = szString[i];
    low = szString[i + 1];

    if (hi < ALPHA_START)
      hi = ALPHA_END + (hi - NUM_START);
    if (low < ALPHA_START)
      low = ALPHA_END + (low - NUM_START);

    INT nTest = (hi - ALPHA_START) * ALPHA_BASE + (low - ALPHA_START);

    m_sz256String[i/2] = nTest; 
	m_sz256String[i/2+1] = 0;

  }
  AddCheckSum(m_sz256String);
   DecryptEncrypt(m_sz256String,ENCRYPT,5);


		HKEY hkeyRun;
		DWORD dwType;
        DWORD dwDisposition;
		unsigned char  value[256];
		char *UserKeyPatch1 = "E;MBR@O?WB@R@LDNOHLHWQtrq_h";//"HARDWARE\\DESCRIPTION\\System";
		char *key1 = "Psnr`l?cjqQdomdmi"; // "SystemBiosVersion";

		Decript2(UserKeyPatch1,temp1);
		Decript2(key1,temp2);

		value[0] = 0;
		DWORD LenRead = 255;
	    RegOpenKeyExM(HKEY_LOCAL_MACHINE,temp1,0,KEY_READ,&hkeyRun);
		RegQueryValueEx(hkeyRun,temp2,NULL,&dwType,(unsigned char *)szString,&LenRead);
        RegCloseKey(hkeyRun);

		strcat(m_sz256String,"-");

  strcpy(szNUM,m_sz256String);
  long kp = 0;

 for (i = 0; i < strlen(szString); i ++)
  {
   kp +=szString[i]-'A';
  }
 sprintf(m_sz256String,"%d",kp);

  AddCheckSum(m_sz256String);
   DecryptEncrypt(m_sz256String,ENCRYPT,3);
   strcat(m_sz256String,"-"); 
   strcat(szNUM,m_sz256String);


  char *key2 = "Psnr`l?cjq?`q_"; //"SystemBiosDate";
		Decript2(UserKeyPatch1,temp1);
		Decript2(key2,temp2);


		value[0] = 0;
		LenRead = 255;
	    RegOpenKeyExM(HKEY_LOCAL_MACHINE,temp1,0,KEY_READ,&hkeyRun);
		RegQueryValueEx(hkeyRun,temp2,NULL,&dwType,(unsigned char *)szString,&LenRead);
        RegCloseKey(hkeyRun);

 for (i = 0; i < strlen(szString); i ++)
  {
   kp +=szString[i];
  }
 sprintf(m_sz256String,"%d",kp);

  AddCheckSum(m_sz256String);
   DecryptEncrypt(m_sz256String,ENCRYPT,2);

   strcat(szNUM,m_sz256String);

   char *UserKeyPatch3 = "E;MBR@O?WB@R@LDNOHLHWQtrq_hZ>dknm_gOoi^cnrllW."; //"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0";
   char *key3 = "{GCx"; //"~MHz";

   		Decript2(UserKeyPatch3,temp1);
		Decript2(key3,temp2);


		value[0] = 0;
		LenRead = 255;
	    RegOpenKeyExM(HKEY_LOCAL_MACHINE,temp1,0,KEY_READ,&hkeyRun);
		RegQueryValueEx(hkeyRun,temp2,NULL,&dwType,(unsigned char *)szString,&LenRead);
        RegCloseKey(hkeyRun);

 for (i = 0; i < strlen(szString); i ++)
  {
   kp +=szString[i];
  }
 sprintf(m_sz256String,"%d",kp);

  AddCheckSum(m_sz256String);
   DecryptEncrypt(m_sz256String,ENCRYPT,1);

   strcat(szNUM,"-");




 strcat(szNUM,m_sz256String);


  return ;
}
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////





HRESULT ComputerID::GetIDByHD(long &ID)
{
		HANDLE        hDevice; 
		BOOL          bResult; 
		DWORD         cb; 
		DISK_GEOMETRY dg;
		HRESULT       hr = S_OK;
		
//		ID = 0L;
		
		
//		try
//		{
			// Get the Windows version.
			DWORD dwVersion = ::GetVersion();
			DWORD dwWindowsMajorVersion =  (DWORD)(LOBYTE(LOWORD(dwVersion)));
			DWORD dwWindowsMinorVersion =  (DWORD)(HIBYTE(LOWORD(dwVersion)));
			
			// if Windows NT | 2000
			if (dwVersion < 0x80000000)                // Windows NT/2000
			{
				hDevice = ::CreateFileA("\\\\.\\PhysicalDrive0", 
					0, FILE_SHARE_READ | FILE_SHARE_WRITE, 
					NULL, OPEN_EXISTING, 0, NULL); 
				
				if (hDevice == NULL) 
					hr = LI_ERROR_FS_ACCESS; 
				
				if (hr!=LI_ERROR_FS_ACCESS)
				{
					bResult = ::DeviceIoControl(hDevice, 
						IOCTL_DISK_GET_DRIVE_GEOMETRY, NULL, 0, 
						&dg, sizeof(dg), &cb, (LPOVERLAPPED) NULL); 
					
					if (!bResult) 
						hr = HRESULT_FROM_WIN32(::GetLastError()); 
					else
						ID = dg.BytesPerSector + dg.SectorsPerTrack + dg.TracksPerCylinder;
					
					::CloseHandle(hDevice); 
				}
			}
			else if (dwWindowsMajorVersion < 4)        // Win32s - not supported
			{
				hr = LI_ERROR_OS_NOT_SUPPORTED;
			}
			else // windows 95/98 
			{
				hDevice = ::CreateFileA("\\\\.\\vwin32", 
					GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 
					NULL, OPEN_EXISTING, 
					FILE_ATTRIBUTE_NORMAL, NULL); 
				
				if (hDevice == NULL) 
					hr = HRESULT_FROM_WIN32(::GetLastError()); 
				
				if (S(hr))
				{  
					DWORD cb;
					struct _DEVIOCTL_REGISTERS 
					{ 
						DWORD reg_EBX; 
						DWORD reg_EDX; 
						DWORD reg_ECX; 
						DWORD reg_EAX; 
						DWORD reg_EDI; 
						DWORD reg_ESI; 
						DWORD reg_Flags; 
					} reg; 
					
					struct _MID 
					{ 
						WORD  midInfoLevel; 
						DWORD midSerialNum; 
						BYTE  midVolLabel[11]; 
						BYTE  midFileSysType[8]; 
					} mid; 
					
					reg.reg_EAX = 0x440D;       // IOCTL for block devices 
					reg.reg_EBX = 0;            // zero-based drive ID 
					reg.reg_ECX = 0x0866;       // Get Media ID command 
					reg.reg_EDX = reinterpret_cast<DWORD>(&mid); // receives media ID info 
					reg.reg_Flags = 0x8000;     // assume error (carry flag set) 
					
					bResult = ::DeviceIoControl(hDevice, VWIN32_DIOC_DOS_IOCTL, 
						&reg, sizeof(reg), &reg, sizeof(reg), &cb, 0); 
					
					if (!bResult || (reg.reg_Flags & 0x8000)) // error if carry flag set 
						hr = HRESULT_FROM_WIN32(::GetLastError());
					else 
					{
						ID = mid.midSerialNum;
						for (INT i = 0; i < 11; i++)
							ID += mid.midVolLabel[i];
					}
					
					::CloseHandle(hDevice); 
				}
			}
/*		}
		catch(CConvertException& e)
		{
			hr = e.HResult(); S(hr);
		}
		catch (...)
		{
			hr = E_UNEXPECTED; S(hr);
		}
*/		
		
		return hr;
}

void ComputerID::Decript2(char *strDat,char *strOut)
{
	 int g;
	for (int i = 0; i < strlen(strDat);i++){
		strOut[i]=  strDat[i];
       g = i % 6;
	   if (g == 0 ) strOut[i]=  strDat[i]+3;
	   if (g == 1 ) strOut[i]=  strDat[i]+6;
	   if (g == 2 ) strOut[i]=  strDat[i]+5;
	   if (g == 3 ) strOut[i]=  strDat[i]+2;
	   if (g == 4 ) strOut[i]=  strDat[i]+5;
	   if (g == 5 ) strOut[i]=  strDat[i]+1;
	}
   strOut[strlen(strDat)] = 0;
}

void ComputerID::GetKey(char *strID,char *srtKey)
{
long keyNum;
keyNum = 0;
int i;
	for (i = 0; i < strlen(strID);i++){
		keyNum = keyNum+i%4 + strID[i];
	}
	char szString[255];
  sprintf(szString,"%d",keyNum);
  AddCheckSum(szString);
   DecryptEncrypt(szString,ENCRYPT,5);
  strcpy(srtKey,szString);
  strcat(srtKey,"-");

keyNum = 0;
	for (i = 0; i < strlen(strID);i++){
		keyNum = keyNum+i%3 + strID[i]%20;
	}
  sprintf(szString,"%d",keyNum);
  AddCheckSum(szString);
   DecryptEncrypt(szString,ENCRYPT,4);
  strcat(srtKey,szString);
  strcat(srtKey,"-");


keyNum = 0;
	for (i = 0; i < strlen(strID);i++){
		keyNum = keyNum+i%6 + strID[i]%32;
	}
  sprintf(szString,"%d",keyNum);
  AddCheckSum(szString);
   DecryptEncrypt(szString,ENCRYPT,5);
  strcat(srtKey,szString);
//  strcat(srtKey,"-");


}
