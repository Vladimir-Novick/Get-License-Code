

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


#ifndef BASE64_H
#define BASE64_H

extern void base64_encode(const unsigned char *str, int length,unsigned char *result, int *ret_length);
extern void base64_decode(const unsigned char *str, int length,unsigned char *result, int *ret_length);


#endif /* BASE64_H */
