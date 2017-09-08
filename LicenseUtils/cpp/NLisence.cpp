
///////////////////////////////////////////////////////////////////////////////////////////
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
#include "NLisence.h"
#include "computerID.h"
#include "RegisterSave.h"
#include <stdio.h>
#include <fstream.h>


extern void base64_encode(const unsigned char *str, int length,unsigned char *result, int *ret_length) ;
extern void base64_decode(const unsigned char *str, int length,unsigned char *result, int *ret_length) ;


extern void mytrim(char *str,char *dest);


LONG RegOpenKeyExM(
  HKEY hKey,         // handle to open key
  LPCTSTR lpSubKey,  // subkey name
  DWORD ulOptions,   // reserved
  REGSAM samDesired, // security access mask
  PHKEY phkResult    // handle to open key
);



void mytrim(char *str,char *dest){
	char temp[255];
	memset(temp,0,255);
	int y = strlen(str);
	int rez = 0;
	for (int i = 0; i < y; i++){
		if ( str[i] != ' '){
           temp[rez]=str[i];
	       rez++;
		}
	}
           temp[rez]=0;
	strcpy(dest,temp);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNLisence::CNLisence()
{

}

CNLisence::~CNLisence()
{

}

VOID CNLisence::GetComputerCode(char *strBuffer)
{

}

int CNLisence::CheckLicense(char *strBuffer)
{
 return 1;
}

int CNLisence::CheckLicenseForStart(VOID)
{
	char strUserID[255];
	char strUserID1[255];
	char strKey[255];
	char strKey1[255];
			  strUserID1[0]=0;
		 CRegisterSave *mReg;
          mReg = new CRegisterSave;
		 mReg->UserKeyStore("UserID",strUserID1,255,CRegisterSave::READ);
			mytrim(strUserID1,strUserID);

		 		  strKey1[0] = 0;
		 mReg->UserKeyStore("Key",strKey1,255,CRegisterSave::READ);
		 		mytrim(strKey1,strKey);


				  ComputerID *pID ;
				  pID = new ComputerID;
				  char strDat[256];
				  strDat[0]=0;
				  pID->GetComuterID(strDat);
		          strcat(strDat,strUserID);
				  char strVer[255];


                  mycrypt(strDat, strVer);
				  delete pID;
				  delete mReg;

				  if (strcmp(strVer,strKey)== 0 ) {
                      return 1;
				  }


				  if (CheckFullTrial()== TRUE ){
					  return 2;
				  }

				  return 0;
}

void CNLisence::mycrypt(char *source, char *desc)
{

	char nstr[255];
	char str[255];
	char source1[255];
	double sum1;
	int rett;
	long len;
	char repla[255];
  sum1 = 0;
  len = strlen(source);
    for (int i=0;i<len;i++) {
      sum1 += source[i]*(255*i);
    }
    sprintf(source1,"%.0f",sum1); 
 
  
  base64_encode((unsigned char *)source1,strlen(source1),(unsigned char *)str,&rett);

  int iu;

  for (iu=0;str[iu] != 0; iu++){

    if (str[iu]=='-'){ str[iu] = '9';}
    if (str[iu]=='#'){ str[iu] = 'Z';}
    if (str[iu]=='N'){ str[iu] = '0';}

  }
  



  base64_encode((unsigned char *)str,strlen(str),(unsigned char *)repla,&rett);

  for (iu=0;repla[iu] != 0; iu++){
   
	if (repla[iu]=='-'){ repla[iu] = 'N';}
    if (repla[iu]=='#'){ repla[iu] = 'Z';}
    if (repla[iu]=='M'){ repla[iu] = '0';}
    if (repla[iu]=='n'){ repla[iu] = '8';}
    if (repla[iu]=='a'){ repla[iu] = '6';}
    if (repla[iu]=='e'){ repla[iu] = '4';}
    if (repla[iu]=='w'){ repla[iu] = '2';}
    if (repla[iu]=='k'){ repla[iu] = '5';}
    if (repla[iu]=='q'){ repla[iu] = '7';}

  }


  
    int ip;
	ip = 0;
	int iuN = 0;
    for (iu=0;repla[iu] != 0;iu++) {
      ip ++;
      if (ip == 5){
        nstr[iuN]='-';
		iuN++;
        ip = 0;
	  }
	  nstr[iuN] = repla[iu];
	  iuN++;
	  nstr[iuN] = 0;
    } 


  strcpy(desc,nstr);

}


/*

BOOL CNLisence::RegisterString (
   LPSTR pszKey, 
   LPSTR pszValue, 
   LPSTR pszData
   )
{

    HKEY hKey;
    DWORD dwDisposition;

    //
    // Create the key, if it exists it will be opened
    //

    if (ERROR_SUCCESS != 
        RegCreateKeyEx(
//          HKEY_LOCAL_MACHINE,       // handle of an open key 
          pszKey,                  // address of subkey name 
          0,                       // reserved 
          NULL,                    // address of class string 
          REG_OPTION_NON_VOLATILE, // special options flag 
          KEY_ALL_ACCESS,           // desired security access 
          NULL,                       // address of key security structure 
          &hKey,                   // address of buffer for opened handle  
          &dwDisposition))            // address of disposition value buffer 
    {
        return FALSE;
    }

    //
    // Write the value and it's data to the key
    //

    if (ERROR_SUCCESS != 
        RegSetValueEx(
            hKey,                 // handle of key to set value for  
            pszValue,             // address of value to set 
            0,                     // reserved 
            REG_SZ,                 // flag for value type 
            (const unsigned char *)pszData,             // address of value data 
            strlen(pszData) ))      // size of value data 
    {
        
        RegCloseKey(hKey);
        return FALSE;
    }

    //
    // Close the key
    //
    
    RegCloseKey(hKey);
    
    return TRUE;
}

*/
/*
BOOL CNLisence::GetRegString (
  LPSTR pszKey,
  LPSTR pszValue,
  LPSTR pszData
  )
{

    HKEY hKey;
    DWORD dwDataSize = MAX_PATH - 1;
    DWORD dwValueType = REG_SZ;

    RegOpenKeyExM(
//       HKEY_LOCAL_MACHINE,    // handle of open key 
       pszKey,                // address of name of subkey to open 
       0,                    // reserved 
       KEY_QUERY_VALUE,        // security access mask 
       &hKey                 // address of handle of open key 
       );    

    RegQueryValueEx(
        hKey,         // handle of key to query 
        pszValue,     // address of name of value to query 
        0,             // reserved 
        &dwValueType,// address of buffer for value type 
        (unsigned char *)pszData,     // address of data buffer 
        &dwDataSize  // address of data buffer size 
        );

    if (pszData[dwDataSize] != '\0')
        pszData[dwDataSize] = '\0';

    return TRUE;
}

*/

BOOL CNLisence::CheckFullTrial()
{

SYSTEMTIME SystemTimeStart;

	GetSystemTime(
  &SystemTimeStart   // system time
);


	char strEdictKey[50];





// {D2C8128C-D2DF-430A-889B-9C1C1D8764F2}

// HKEY_CURRENT_USER

	 char source1[255];
	 char fTime[255];
	 char fTime2[255];
//	 strcpy(fTime,"MjAwMiwwNSwxNQ--");
	 // MjAwMiwwNiwxNA--    MjAwMiwwNSwzMA--
	 //strcpy(fTime,"MjAwMiwwNiwyOA--");
//	 strcpy(fTime,"MjAwMiwwNywyNg--");
	 GetStartDate(fTime);
 char str[255];
 char str1[255];
 int rett;
 int strLen2;
 	 long ldayFin ;
	 long ldayCur ; 

	 int t1 ;//= 2002;
	 int t2 ;//= 5;
	 int t3 ;//= 15;
// 	 sprintf(source1,"%04d,%02d,%02d",t1,t2,t3);
 	 sprintf(source1,"%04d,%02d,%02d",SystemTimeStart.wYear,SystemTimeStart.wMonth,SystemTimeStart.wDay);
	 base64_encode((unsigned char *)source1,strlen(source1),(unsigned char *)str,&strLen2);
	 str[strLen2]=0;

		 CRegisterSave *mReg;
          mReg = new CRegisterSave;

         str1[0]=0;
		 mReg->UserKeyStore("Compression",str1,100,CRegisterSave::READ);
		 rett = strlen(str1);
		 int ty1 = 0;
			 char tb[255];
		 mReg->UserKeyStore("ShowToolbar",tb,100,CRegisterSave::READ);
		  ty1 = strlen(tb);


         if ((ty1 > 0 ) && (rett==0)){
		  delete mReg;
          return FALSE;
		 }


         if (rett > 5 ){
			 int rett1=0;
	        base64_decode((unsigned char *)str1,rett,(unsigned char *)fTime2,&rett1);
	 if (rett1 = 0 ){
		delete mReg;
        return FALSE;
	 }


	        fTime2[4] = 0;
	        fTime2[7] = 0;

	        t1= atoi(fTime2);
	        t2= atoi(&fTime2[5]);
	        t3= atoi(&fTime2[8]);


	 ldayFin = (t1-2001)*365+t2*31 + t3;
	 ldayCur = (SystemTimeStart.wYear-2001)*365 + (SystemTimeStart.wMonth*31) + SystemTimeStart.wDay; 

	 if (ldayFin > ldayCur ){
		delete mReg;
        return FALSE;
	 }


	 ldayFin = (SystemTimeStart.wYear-2001)*365 + (SystemTimeStart.wMonth*31) + SystemTimeStart.wDay; 
	 ldayCur = 365 + 122 + 15; 

	 if (ldayFin < ldayCur ){
		delete mReg;
      return FALSE;
	 }


		 }

/*     char * NKeyM = "%USERPROFILE%\\Local Settings\\Temp";
	 JVVTRVJQUk9GSUxFJVxMb2NhbCBTZXR0aW5nc1xUZW1w



     char NKey3[400];
	 base64_encode((unsigned char *)NKeyM,strlen(NKeyM),(unsigned char *)NKey3,&rett);
	 NKey3[rett]=0;
	 mReg->UserKeyStore("Compression1",NKey3,rett,CRegisterSave::WRITE);
*/

		 mReg->UserKeyStore("Compression",str,strLen2,CRegisterSave::WRITE);
		 delete mReg;

	 base64_decode((unsigned char *)fTime,strlen(fTime),(unsigned char *)fTime2,&rett);
	 fTime2[4] = 0;
	 fTime2[7] = 0;

	 t1= atoi(fTime2);
	 t2= atoi(&fTime2[5]);
	 t3= atoi(&fTime2[8]);
	 ldayFin = (t1-2001)*365+t2*31 + t3;
	 ldayCur = (SystemTimeStart.wYear-2001)*365 + (SystemTimeStart.wMonth*31) + SystemTimeStart.wDay; 

	 if (ldayFin >= ldayCur ){
        return TRUE;
	 }
		 

   return FALSE;
}

void CNLisence::GetStartDate(char *strStart)
{
	HKEY hCU;
	DWORD lpType;
	char CurrentSetDate[255];
	ULONG ulSize;

	char cmdLine[255];
	strcpy(cmdLine,GetCommandLine());

SYSTEMTIME SystemTimeStart;

	GetSystemTime(
  &SystemTimeStart   // system time
);

	

	char source1[255];
	 int t1 = SystemTimeStart.wYear;
	 int t2 = SystemTimeStart.wMonth;
	 int t3 = SystemTimeStart.wDay;


t3 = t3 + 14;
if (t3 > 28 ){
	t3 = 1;
	t2 += 1;
}

if (t2 > 12 ) {
	t2=1;
	t1+= 1;
}
 	 sprintf(source1,"%04d,%02d,%02d",t1,t2,t3);
	 char str[255];
	 char str1[255];
	 str[0]=0;
	 str1[0]=0;
  	 int strLen2;
	 base64_encode((unsigned char *)source1,strlen(source1),(unsigned char *)str1,&strLen2);
	 str1[strLen2]=0;
	 base64_encode((unsigned char *)str1,strlen(str1),(unsigned char *)str,&strLen2);
	 int kkl = strlen(str);
	 for (int ip2 = 0 ; ip2 < kkl; ip2 ++ ){
		 if (str[ip2] == '-'){
			str[ip2] = '_';
		 }
	 }



//  Software\Microsoft\Windows\CurrentVersion\Explorer\Shell Folders
//	U29mdHdhcmVcTWljcm9zb2Z0XFdpbmRvd3NcQ3VycmVudFZlcnNpb25cRXhwbG9yZXJcU2hlbGwgRm9sZGVycw--


//  Environment
// RW52aXJvbm1lbnQ-

//	     char * NKeyM = "%USERPROFILE%\\Local Settings\\Temp";
	 char * NKeyM ="JVVTRVJQUk9GSUxFJVxMb2NhbCBTZXR0aW5nc1xUZW1w";
				int rett;
				char NKeyM_D[255];
					NKeyM_D[0]=0;
	     base64_decode((unsigned char *)NKeyM,strlen(NKeyM),(unsigned char *)NKeyM_D,&rett);
		 

    ulSize = 255;
	char *StrKey = "TempNd32";
	CurrentSetDate[0]=0;
		if (RegOpenKeyExM(HKEY_CURRENT_USER, 
			"Environment", 
			0,KEY_QUERY_VALUE,
			&hCU) == ERROR_SUCCESS)
		{
			RegQueryValueEx( hCU,
				StrKey,
				NULL,
				&lpType,
				(unsigned char *)CurrentSetDate,
				&ulSize);

			char strStart1[255];

			if (strlen(CurrentSetDate) >  0 ) {
			if (strlen(CurrentSetDate) < 34 ){
				strcpy(strStart,"MjAwMiwwNiwyOA--");
			} else {
				strcpy(strStart1,&CurrentSetDate[34]);
				if (strlen(strStart1) < 7 ){
				  strcpy(strStart,"MjAwMiwwNSwxNQ--");
				} else {
				  strStart1[strlen(strStart1)-4] = 0;


				 for (int ip2 = 0 ; ip2 < strlen(strStart1); ip2 ++ ){
					 if (strStart1[ip2] == '_'){
						strStart1[ip2] = '-';
					 } else {
						strStart1[ip2] = strStart1[ip2];
					 }
				 }

	              base64_decode((unsigned char *)strStart1,strlen(strStart1),(unsigned char *)strStart,&rett);
				  strStart1[rett]=0;
				  strStart[rett]=0;






				}
			}
		}



			RegCloseKey(hCU);
		}
//
		if (strlen(CurrentSetDate) == 0 ) {
		if (RegOpenKeyExM(HKEY_CURRENT_USER, 
			"Environment", 
			0,KEY_WRITE,
			&hCU) == ERROR_SUCCESS)
		{

		char value[255];
		strcpy(value,NKeyM_D);
		strcat(value,"\\");
		strcat(value,str);
		strcat(value,".tmp");
//
unsigned long LenRead;

			if (CheckGetTempDate() == FALSE ){
				strcpy(strStart,"MjAwMiwwNiwyOA--");
				char *pl = "%USERPROFILE%\\Local Settings\\Temp\\TWpBd01pd3dPU3d4TnctLQ__.tmp";
	            LenRead = strlen(pl);
		        RegSetValueEx(hCU,StrKey,0,REG_SZ,(const unsigned char *)pl,LenRead);
			} else {


	LenRead = strlen(value);
		RegSetValueEx(hCU,StrKey,0,REG_SZ,(const unsigned char *)value,LenRead);
		strcpy(strStart,str1);
			}

			RegCloseKey(hCU);
			SetProtectGetDate();
		}



		}



}


extern char lpCommand[255];

BOOL CNLisence::CheckGetTempDate(void)
{
	   return TRUE;
}

BOOL CNLisence::SetProtectGetDate()
{
return TRUE;
}
