#include <stdio.h>
#include <string.h>
#include "hmac/KISA_HMAC.h"
#include "hmac/KISA_SHA256.h"
#include "hmac/util.h"
#include "hmac/b64.h"

struct JToken
{
	char* header;
	char* payload;
	char* verify;
};

struct JToken_H
{
	char* alg;
	char* typ;
};

struct JToken_P
{
	char* iss;
	char* user;
	char* token;
	char* exp;
	char* iat;
};

int main(int argc, char** argv)
{
	unsigned char msg[1024] = {0,}, key[1024] = {0,}, hmac[32];
	unsigned int msgLen = 0, keyLen = 0, outputLen = 0, ret = 0;

	char* OP = NULL;
	char* MSG = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJBdXRoLVRlc3QiLCJ1c2VyIjoidGVzdGFjY291bnRzMSIsInRva2VuIjoiYWNjZXNzX3Rva2VuIiwiZXhwIjoiMTY4NzM0NDUwOSIsImlhdCI6IjE2ODczNDI3MDkifQ.NqQ0n-W3nWvLuPbhSYDARfz1qox-86GB4iuXWDMoiy4";
	char* KEY = "2JkpyD4C5v_qW=nzKkGCKCG-hhhb6K&2sk+m-72s^ntMXWC3fHUt^b6s7Ksg7DmA";
	char* TOKEN = "{\"token\":\"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJBdXRoLVRlc3QiLCJ1c2VyIjoidGVzdGFjY291bnRzMyIsInRva2VuIjoiYWNjZXNzX3Rva2VuIiwiZXhwIjoiMTY4OTY4Mzg1MCIsImlhdCI6IjE2ODk2ODIwNTAifQ.37ntURjhiWlDZ0PEps3XYY5cby1B2r7wVcqggITznJ4\"}";

	char* newstr;
	char* ptr;
	char* next_ptr;

	struct JToken jtk;

	int i = 0;

	newstr = strdup(MSG);

	printf("msg: %s\n", newstr);

	ptr = strtok_r(newstr, ".", &next_ptr);

	while(ptr)
	{
		printf("ptr = %s\n", ptr);

		switch(i)
		{
			case 0: jtk.header = strdup(ptr);
				break;
			case 1: jtk.payload = strdup(ptr);
				break;
			case 2: jtk.verify = strdup(ptr);
				break;
		}

		ptr = strtok_r(NULL, ".", &next_ptr);
		i++;
	}

	int headLen = strlen(jtk.header);
	char* _header = malloc(3*(headLen / 4));
	base64d(jtk.header, _header, &headLen);


	int plLen = strlen(jtk.payload);
	char* _payload = malloc(3*(plLen / 4));
	base64d(jtk.payload, _payload, &plLen);

	printf("header: %s\n", jtk.header);
	printf("header: %s\n", _header);
	_header[strlen(_header)-1] = '\0';
	printf("headers: %s\n", _header+1);
	struct JToken_H jtk_h;


	printf("payload: %s\n", jtk.payload);
	printf("payload: %s\n", _payload);
	char* ptrs = strchr(_payload, '}');
	ptrs[0] = '\0';
	printf("payloads: %s\n", _payload+1);
	struct JToken_P jtk_p;


	printf("verify: %s\n", jtk.verify);

	free(newstr);
	free(_header);
	free(_payload);
	free(jtk.header);
	free(jtk.payload);
	free(jtk.verify);
	

	return 0;
}
