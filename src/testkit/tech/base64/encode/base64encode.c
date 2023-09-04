#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <endian.h>

static const char MimeBase64[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

typedef union
{
	struct
	{
		unsigned char c1,c2,c3;
	};

	struct
	{
		unsigned int e1:6,e2:6,e3:6,e4:6;
	};
} BF;
 
int endian = 0; // little : 0, big : 1
  
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

int main()
{
	char* TTEE = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
	char* result;
	int src_len = strlen(TTEE);

	result = (char*)malloc((4 * (src_len / 3)) + (src_len % 3 ? 4 : 0) + 1);

	base64e(TTEE, result, src_len);

	printf("%s\n", TTEE);
	printf("%s\n", result);
	printf("%d\n", src_len);


	return 0;
}
