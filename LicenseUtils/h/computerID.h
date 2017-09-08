
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



#if !defined(AFX_OMPUTERID_H__FE585C7E_F4E5_49A5_BBCA_30918CCDD7C8__INCLUDED_)
#define AFX_OMPUTERID_H__FE585C7E_F4E5_49A5_BBCA_30918CCDD7C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//   Error File Access
#define LI_ERROR_FS_ACCESS -1
// // Win32s - not supported
#define LI_ERROR_OS_NOT_SUPPORTED  -2 

#define VWIN32_DIOC_DOS_IOCTL 1

#define ALPHA_START 101
#define ALPHA_END   140
#define NUM_START 9
#define ALPHA_BASE 101

enum {ENCRYPT,DECRYPT};


#undef S
#define S(hr) (hr == S_OK)


const short NUM_ENCRYPTION_KEYS = 12;
const short CSLENGTH = 2; 



class ComputerID  
{
private:
	HRESULT GetIDByHD(long &ID);
public:
	void GetKey(char *strID,char *srtKey);
	void Decript2(char *strDat,char *strOut);
    void SwapCheckSum (char * License);
    bool ComputerID::ValidCheckSum(char * s);
    void AddCheckSum(char * s);
    void DecryptEncrypt(char * inputString, int operation, int random_key);
	void  GetComuterID(char * szNUM);  
	ComputerID();
	virtual ~ComputerID();

};

#endif // !defined(AFX_OMPUTERID_H__FE585C7E_F4E5_49A5_BBCA_30918CCDD7C8__INCLUDED_)
