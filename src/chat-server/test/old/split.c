#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SEPS ":"

ch

int main()
{
	char* TOKEN = "{\"token\":\"eyJhbiGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJBdXRoLVRlc3QiLCJ1c2VyIjoidGVzdGFjY291bnRzMyIsInRva2VuIjoiYWNjZXNzX3Rva2VuIiwiZXhwIjoiMTY4OTY4Mzg1MCIsImlhdCI6IjE2ODk2ODIwNTAifQ.37ntURjhiWlDZ0PEps3XYY5cby1B2r7wVcqggITznJ4\"}";
	
	char* token;
	char* ret_ptr;
	char* next_ptr;

	token = strdup(TOKEN+1);

	char* ptrs = strchr(token, '}');
	ptrs[0] = '\0';

	printf("token: %s\n", token);

	ret_ptr = strtok_r(token, SEPS, &next_ptr);

	while(ret_ptr)
	{
		printf("ret_ptr = %s\n", ret_ptr);

		ret_ptr = strtok_r(NULL, SEPS, &next_ptr);
	}

	free(token);

	return 0;
}

char** jparse(char* _msg, char* key, char* data)
{
	char* msg = strdup(_msg+1);

	char* ptrs = strchr(msg, '}');
	ptrs[0] = '\0';

	

	free(msg);
}
