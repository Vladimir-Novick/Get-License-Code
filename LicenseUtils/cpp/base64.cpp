
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

#include "base64.h"

static char base64_table[] =
	{ 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
	  'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
	  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	  'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
	  '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '#', '/', '\0'
	};




static char base64_pad = '-';

void base64_encode(const unsigned char *str, int length,unsigned char *result, int *ret_length) {
	const unsigned char *current = str;
	int i = 0;

	while (length > 2) { /* keep going until we have less than 24 bits */
		result[i++] = base64_table[current[0] >> 2];
		result[i++] = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
		result[i++] = base64_table[((current[1] & 0x0f) << 2) + (current[2] >> 6)];
		result[i++] = base64_table[current[2] & 0x3f];

		current += 3;
		length -= 3; /* we just handle 3 octets of data */
	}


	if (length != 0) {
		result[i++] = base64_table[current[0] >> 2];
		if (length > 1) {
			result[i++] = base64_table[((current[0] & 0x03) << 4) + (current[1] >> 4)];
			result[i++] = base64_table[(current[1] & 0x0f) << 2];
			result[i++] = base64_pad;
		}
		else {
			result[i++] = base64_table[(current[0] & 0x03) << 4];
			result[i++] = base64_pad;
			result[i++] = base64_pad;
		}
	}
	if(ret_length) {
		*ret_length = i;
	}
	result[i] = '\0';
	return;
}


void base64_decode(const unsigned char *str, int length,unsigned char *result, int *ret_length) {
	const unsigned char *current = str;
	int ch, i = 0, j = 0, k;

	static short reverse_table[256];
	static int table_built;
	

	if (++table_built == 1) {
		char *chp;
		for(ch = 0; ch < 256; ch++) {
			chp = strchr(base64_table, ch);
			if(chp) {
				reverse_table[ch] = chp - base64_table;
			} else {
				reverse_table[ch] = -1;
			}
		}
	}



	while ((ch = *current++) != '\0') {
		if (ch == base64_pad) break;

		if (ch == ' ') ch = '+'; 

		ch = reverse_table[ch];
		if (ch < 0) continue;

		switch(i % 4) {
		case 0:
			result[j] = ch << 2;
			break;
		case 1:
			result[j++] |= ch >> 4;
			result[j] = (ch & 0x0f) << 4;
			break;
		case 2:
			result[j++] |= ch >>2;
			result[j] = (ch & 0x03) << 6;
			break;
		case 3:
			result[j++] |= ch;
			break;
		}
		i++;
	}

	k = j;

	if (ch == base64_pad) {
		switch(i % 4) {
		case 0:
		case 1:
	        *ret_length = 0;
			return;
		case 2:
			k++;
		case 3:
			result[k++] = 0;
		}
	}
	if(ret_length) {
		*ret_length = j;
	}
	result[k] = '\0';
	return ;
}

