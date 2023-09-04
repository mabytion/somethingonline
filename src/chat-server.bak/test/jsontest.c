#include <stdio.h>
#include "../header/json-c.h"

int main()
{
    struct node** hashTable = createHashTable();

	char* TOKEN = "{\"token\":\"eyJhbiGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJBdXRoLVRlc3QiLCJ1c2VyIjoidGVzdGFjY291bnRzMyIsInRva2VuIjoiYWNjZXNzX3Rva2VuIiwiZXhwIjoiMTY4OTY4Mzg1MCIsImlhdCI6IjE2ODk2ODIwNTAifQ.37ntURjhiWlDZ0PEps3XYY5cby1B2r7wVcqggITznJ4\"}";

	char* TO = "{\"iss\":\"eee\",\"eet\":\"yyy\",\"aas\":\"zzz\",\"zxd\":\"xxx\",\"aqw\":\"www\"}";;

//	parseJSON(&hashTable, TOKEN);
	parseJSON(&hashTable, TO);

	printTable(&hashTable);


	char* TOO = createJSON(&hashTable);

	printf("%s\n", TOO);

	free(TOO);
	deleteTable(&hashTable);

	return 0;
}
