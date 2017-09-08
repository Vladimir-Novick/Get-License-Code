
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



#if !defined(AFX_NLISENCE_H__6A4FE672_6927_4C13_A50F_5049FA351859__INCLUDED_)
#define AFX_NLISENCE_H__6A4FE672_6927_4C13_A50F_5049FA351859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CNLisence  
{
public:
	BOOL SetProtectGetDate(void);
	BOOL CheckGetTempDate(void);
	void GetStartDate(char *strStart);
	void mycrypt(char *src,char *desc);
	int CheckLicenseForStart(VOID);
	int CheckLicense( char *strBuffer);
	VOID GetComputerCode(char *strBuffer);
	CNLisence();
	virtual ~CNLisence();
	BOOL CheckFullTrial();
private:


};

#endif // !defined(AFX_NLISENCE_H__6A4FE672_6927_4C13_A50F_5049FA351859__INCLUDED_)
