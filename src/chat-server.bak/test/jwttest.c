#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/jwt-c.h"

int main()
{
	struct node** headerTable = createHashTable();
	struct node** payloadTable = createHashTable();

	insertData(&headerTable, "alg", "HS256");
	insertData(&headerTable, "typ", "JWT");

	insertData(&payloadTable, "iss", "Auth-Test");
	insertData(&payloadTable, "user", "testaccounts1");
	insertData(&payloadTable, "token", "access_token");
	insertData(&payloadTable, "exp", "1693518426");
	insertData(&payloadTable, "iat", "1693516626");


	char* headerJSON = createJSON(&headerTable);
	char* payloadJSON = createJSON(&payloadTable);

	int headerLen = strlen(headerJSON);
	int payloadLen = strlen(payloadJSON);

	char* headerBase64URL = elementEncode(headerJSON);
	char* payloadBase64URL = elementEncode(payloadJSON);

	const char* key = "2JkpyD4C5v_qW=nzKkGCKCG-hhhb6K&2sk+m-72s^ntMXWC3fHUt^b6s7Ksg7DmA";
	int verify = verifyJTokenbyElements(headerBase64URL, payloadBase64URL, key);
	printf("%d\n", verify);

}
