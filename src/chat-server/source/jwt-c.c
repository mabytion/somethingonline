#include "../header/jwt-c.h"

struct JToken* createJToken()
{
	struct JToken* token = (struct JToken*)malloc(sizeof(struct JToken) * 1);

	return token;
}

void initJToken(struct JToken* token, char* str)
{
	int i = 0, j;

	char* ret_ptr;
	char* next_ptr;
	
	ret_ptr = strtok_r(str, ".", &next_ptr);

	while(ret_ptr)
	{
		switch(i)
		{
			case 0: token->header = strdup(ret_ptr);
				break;
			case 1: token->payload = strdup(ret_ptr); 
				break;
			case 2: token->verify = strdup(ret_ptr);
				break;
		}

#ifdef DEBUG
		printf("ret_ptr: %s %d\n", ret_ptr, strlen(ret_ptr));
#endif

		ret_ptr = strtok_r(NULL, ".", &next_ptr);
		i++;
	}

	if(i == 3)
	{
		token->status = 1;

	#ifdef DEBUG
		printf("header: %s %d\n", token->header, strlen(token->header));
		printf("payload: %s %d\n", token->payload, strlen(token->payload));
		printf("verify: %s %d\n", token->verify, strlen(token->verify));
		printf("status: %d\n", token->status);
	#endif
	}
	else
	{
		token->status = 0;
	}
}

void freeJToken(struct JToken* token)
{
#ifdef DEBUG
	printf("======== freeJToken() ========\n");
#endif
#ifdef DEBUG
	printf("free: %p\n", token->header);
#endif
	free(token->header);
#ifdef DEBUG
	printf("free: %p\n", token->payload);
#endif
	free(token->payload);
#ifdef DEBUG
	printf("free: %p\n", token->verify);
#endif
	free(token->verify);
#ifdef DEBUG
	printf("free: %p\n", token);
#endif
	free(token);

#ifdef DEBUG
	printf("=================================\n");
#endif
}

struct JToken* decodeJToken(struct JToken* token)
{
	if(token == (void*)0)
		return token;

	if(token->status & JWT_ENCODED)
	{
		token->header = elementDecode(token->header);
		token->payload = elementDecode(token->payload);
		setDecoded(token, 1);
	}
	else
	{
		printf("Decode err\n");
	}

	return token;
}

char* elementDecode(char* element)
{
	int strLen;
	int memCarry;
	int memSize;

	strLen = strlen(element);
	memCarry = (strLen * 3) % 4 ? 0 : 1;
	memSize = (strLen * 3) / 4 + memCarry + 1;

	char* res = (char*)malloc(memSize);

	base64dURL(element, res, &strLen);
	res[memSize] = '\0';

	free(element);
#ifdef DEBUG
	printf("======== elementDecode() ========\n");
	printf("free: %p\n", element);
	printf("res: %p\n", res);
	printf("strlen: %d\n", strLen);
	printf("=================================\n");
#endif

	return res;
}

char* elementDecode_n(char* element, int len)
{
	int strLen = len;
	int memCarry;
	int memSize;

	memCarry = (strLen * 3) % 4 ? 0 : 1;
	memSize = (strLen * 3) / 4 + memCarry + 1;

	char* res = (char*)malloc(memSize);

	base64dURL(element, res, &strLen);
	res[memSize] = '\0';

	free(element);

	return res;
}

struct JToken* encodeJToken(struct JToken* token)
{
	if(token == (void*)0)
		return token;

	if(token->status & JWT_DECODED)
	{
		token->header = elementEncode(token->header);
		token->payload = elementEncode(token->payload);
		setEncoded(token, 1);
		return token;
	}
	else
	{
		printf("Encode err\n");
	}

	return token;
}

char* elementEncode(char* element)
{
	int strLen;
	int memSize;
	int memCarry;

	strLen = strlen(element);
	memCarry = (strLen * 4) % 3 ? 1 : 0;
	memSize = (strLen * 4) / 3 + memCarry + 1;

	char* res = (char*)malloc(memSize);

	base64eURL(element, res, strLen);
	res[memSize] = '\0';
#ifdef DEBUG
	printf("======== elementEncode() ========\n");
	printf("free: %p\n", element);
	printf("res: %p\n", res);
	printf("=================================\n");
#endif
	free(element);

	return res;
}

unsigned char* elementEncode_n(unsigned char* element, int len)
{
	int strLen = len;
	int memSize;
	int memCarry;

	memCarry = (strLen * 4) % 3 ? 1 : 0;
	memSize = (strLen * 4) / 3 + memCarry + 1;

	char* res = (char*)malloc(memSize);

	base64eURL(element, res, strLen);
	res[memSize] = '\0';

	free(element);

	return res;
}

struct JToken* verifyJToken(struct JToken* token, const char* key)
{
	if(token == (void*)0)
		return token;

	unsigned char hmac[32] = {0,};
	unsigned int keyLen = 0, msgLen = 0, ret = 0;
	char* msg;

	if(token->status & JWT_ENCODED)
	{
		msg = createVerifyTargetString(token);

		keyLen = strlen(key);
		msgLen = strlen(msg);
		
		HMAC_SHA256(msg, msgLen, key, keyLen, hmac);

		token->verify = elementDecode(token->verify);

		if(ret = verifying(token->verify, hmac, 32))
		{
			setVerified(token, 1);
			printf("verified!!!!!\n");
			return token;
		}
		else
		{
			setVerified(token, 0);
			printf("cant sleep\n");
		}

	}
	else
	{
		printf("Verify err\n");
	}

	
	return (void*)0;
}

int verifyJTokenbyElements(char* header, char* payload, const char* key)
{
	unsigned char hmac[32] = {0,};
	unsigned int keyLen = 0, msgLen = 0, ret = 0;
	char* msg;

	msg = createVerifyTargetStringbyElements(header, payload);

	keyLen = strlen(key);
	msgLen = strlen(msg);

	HMAC_SHA256(msg, msgLen, key, keyLen, hmac);

	unsigned char* tmp = elementEncode_n(hmac, 32);

	unsigned char* test = "2wGwG0qD2-IWYbIMku63Jrtq9wKQT0TrAHt749v0Z_n";
	unsigned char* test_buf = elementDecode_n(test, 32);

	ret = verifying(test_buf, hmac, 32);

	if(ret)
	{
		printf("verified!!!!!\n");
		return 1;
	}
	else
	{
		printf("cant sleep\n");
		return 0;
	}
}

int verifying(unsigned char* a, unsigned char* b, int n)
{
	int i;

	for(i=0;i<n;i++)
	{
		if(a[i] != b[i])
			return 0;
	}

	return 1;

}

char* createVerifyTargetString(struct JToken* token)
{
	char* tmp;
	int headerLen;
	int payloadLen;
	int cursor = 0;
	int i;
	
	headerLen = strlen(token->header);
	payloadLen = strlen(token->payload);
	tmp = (char*)malloc(sizeof(char) * (headerLen + payloadLen + 2));
	
	for(i=0;i<headerLen;i++)
	{
		tmp[cursor++] = token->header[i];
	}
	
	tmp[cursor++] = '.';

	for(i=0;i<payloadLen;i++)
	{
		tmp[cursor++] = token->payload[i];
	}

	tmp[cursor] = '\0';

	return tmp;
}

char* createVerifyTargetStringbyElements(char* header, char* payload)
{
	char* tmp;
	int headerLen;
	int payloadLen;
	int cursor = 0;
	int i;
	
	headerLen = strlen(header);
	payloadLen = strlen(payload);
	tmp = (char*)malloc(sizeof(char) * (headerLen + payloadLen + 2));

	printf("headerLen: %d\n", headerLen);
	printf("payloadLen: %d\n", payloadLen);
	
	for(i=0;i<headerLen;i++)
	{
		tmp[cursor++] = header[i];
	}
	
	tmp[cursor++] = '.';

	for(i=0;i<payloadLen;i++)
	{
		tmp[cursor++] = payload[i];
	}

	tmp[cursor] = '\0';
	printf("cursor: %d\n", cursor);
	printf("maybe: %d\n", headerLen+payloadLen);

	return tmp;
}

void setEncoded(struct JToken* token, int n)
{
	if(n)
	{
		token->status |= 1;
	}
	else
	{
		token->status &= 6;
	}
}

void setDecoded(struct JToken* token, int n)
{
	if(n)
	{
		token->status |= 2;
	}
	else
	{
		token->status &= 5;
	}
}

void setVerified(struct JToken* token, int n)
{
	if(n)
	{
		token->status |= 4;
	}
	else
	{
		token->status &= 3;
	}
}

