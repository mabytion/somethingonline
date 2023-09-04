#include "../../header/KISA_HMAC.h"
#include "../../header/KISA_SHA256.h"
#include "../../header/util.h"
#include "../../header/b64.h"



int main()
{
	unsigned char msg[1024] = {0,}, key[1024] = {0,}, output[32] = {0,}, hmac[32];
	unsigned int msgLen = 0, keyLen = 0, outputLen = 0, ret = 0;
	char* OP = NULL;
	char* OUTPUT = "2wGwG0qD2-IWYbIMku63Jrtq9wKQT0TrAHt749v0Z_k";
	char* TE = "eyJpc3MiOiJBdXRoLVRlc3QiLCJ1c2VyIjoidGVzdGFjY291bnRzMSIsInRva2VuIjoiYWNjZXNzX3Rva2VuIiwiZXhwIjoiMTY5MzUxODQyNiIsImlhdCI6IjE2OTM1MTY2MjYifQ";
	char* MSG = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJBdXRoLVRlc3QiLCJ1c2VyIjoidGVzdGFjY291bnRzMSIsInRva2VuIjoiYWNjZXNzX3Rva2VuIiwiZXhwIjoiMTY5MzUxODQyNiIsImlhdCI6IjE2OTM1MTY2MjYifQ";
	char* KEY = "2JkpyD4C5v_qW=nzKkGCKCG-hhhb6K&2sk+m-72s^ntMXWC3fHUt^b6s7Ksg7DmA";

	int OPLen = strlen(OUTPUT);
	int opLen;
	unsigned char ops[32] = {0,};

	OP = (char *)malloc(3 * (OPLen / 4));

	printf("&&&&&&&&&&& test &&&&&&&&&&\n");
	char* TTEE = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";

	printf("HMAC-SHA256-GENERATE _ case 1\n");
	keyLen = strlen(KEY);
	msgLen = strlen(MSG);
	outputLen = asc2hex(output, OUTPUT);

	HMAC_SHA256(MSG, msgLen, KEY, keyLen, hmac);
	printf("msgLen: %d, keyLen: %d\n", msgLen, keyLen);
	printf("hmac: %s\n", hmac);
	print_hex("hmac", hmac, 32);

	printf("-----------------------\n");
	printf("%s\n", OUTPUT);

	int TELen = strlen(OUTPUT);
	char* TETETE = (char*)malloc(3*(TELen / 4));
	base64d(OUTPUT, TETETE, &TELen);
	print_hex("TETETE", TETETE, 32);

	printf("HMAC-SHA256-VERIFY\n");
	ret = Verify_HMAC_SHA256(MSG, msgLen, KEY, keyLen, hmac);

	printf("ret : %d\n", ret);

	free(TETETE);

	return 0;
}
