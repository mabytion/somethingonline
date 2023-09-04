#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>

void base64e(char *src, char *result, int length)
{
	int i, j = 0;
	BF temp;

	if(endian == 0)
	{ // little endian(intel)
		for(i = 0 ; i < length ; i = i+3, j = j+4)
		{
			temp.c3 = src[i];
			if((i+1) > length) temp.c2 = 0x00;
			else temp.c2 = src[i+1];
			if((i+2) > length) temp.c1 = 0x00;
			else temp.c1 = src[i+2];
	    
			result[j]   = MimeBase64[temp.e4];
			result[j+1] = MimeBase64[temp.e3];
			result[j+2] = MimeBase64[temp.e2];
			result[j+3] = MimeBase64[temp.e1];
	 
			if((i+2) > length) result[j+2] = '=';
			if((i+3) > length) result[j+3] = '=';
		}
	}
	else
	{ // big endian(sun)
		for(i = 0 ; i < length ; i = i+3, j = j+4)
		{
			temp.c1 = src[i];
			if((i+1) > length) temp.c2 = 0x00;
			else temp.c2 = src[i+1];
			if((i+2) > length) temp.c3 = 0x00;
			else temp.c3 = src[i+2];
	  
			result[j]   = MimeBase64[temp.e4];
			result[j+1] = MimeBase64[temp.e3];
			result[j+2] = MimeBase64[temp.e2];
			result[j+3] = MimeBase64[temp.e1];
	   
			if((i+2) > length) result[j+2] = '=';
			if((i+3) > length) result[j+3] = '=';
		}
	}
}

void base64d(char* src, char* result, int* length)
{
	int i, j = 0, src_length, blank = 0;
	BF temp;

	src_length = strlen(src);

	if(endian == 0)
	{
		for(i=0;i<src_length;i+=4, j+=3)
		{
			temp.e4 = DecodeMimeBase64[src[i]];
			temp.e3 = DecodeMimeBase64[src[i+1]];
			if(src[i+2] == '=')
			{
				temp.e2 = 0x00;
				blank++;
			}
			else
			{
				temp.e2 = DecodeMimeBase64[src[i+2]];
			}
			if(src[i+3] == '=')
			{
				temp.e1 = 0x00;
				blank++;
			}
			else
			{
				temp.e1 = DecodeMimeBase64[src[i+3]];
			}

			result[j]   = temp.c3;
			result[j+1] = temp.c2;
			result[j+2] = temp.c1;
		}
	}
	else
	{ // big endian(sun)
		for(i = 0 ; i < src_length ; i = i+4, j = j+3){
		temp.e4 = DecodeMimeBase64[src[i]];
		temp.e3 = DecodeMimeBase64[src[i+1]];
		if(src[i+2] == '=')
		{
			temp.e2 = 0x00;
			blank++;
		}
		else
		{
			temp.e2 = DecodeMimeBase64[src[i+2]];
		}

		if(src[i+3] == '=')
		{
			temp.e1 = 0x00;
			blank++;
		}
		else
		{
			temp.e1 = DecodeMimeBase64[src[i+3]];
		}
	 
			result[j]   = temp.c1;
			result[j+1] = temp.c2;
			result[j+2] = temp.c3;
		}
	}
	
	*length = j-blank;
}
