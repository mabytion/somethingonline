#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KISA_HMAC.h"
#include "KISA_SHA256.h"
#include "util.h"
#include "b64.h"
#include "json-c.h"

#ifndef JWT_ENCODED
#define JWT_ENCODED 1
#endif

#ifndef JWT_DECODED
#define JWT_DECODED 2
#endif

#ifndef JWT_VERIFIED
#define JWT_VERIFIED 4
#endif

#ifndef __jwtc__
#define __jwtc__

struct JToken
{
	char* header;
	char* payload;
	char* verify;
	char status;
};


struct JToken* initJToken(char*);
struct JToken* decodeJToken(struct JToken*);
char* elementDecode(char*);
char* elementDecode_n(char*, int);
struct JToken* encodeJToken(struct JToken*);
char* elementEncode(char*);
unsigned char* elementEncode_n(unsigned char*, int);
struct JToken* verifyJToken(struct JToken*, const char*);
int verifyJTokenbyElements(char*, char*, const char*);
int verifying(unsigned char*, unsigned char*, int);
char* createVerifyTargetString(struct JToken*);
char* createVerifyTargetStringbyElements(char*, char*);
void setEncoded(struct JToken*, int);
void setDecoded(struct JToken*, int);
void setVerified(struct JToken*, int);



#endif
