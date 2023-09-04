#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/b64.h"

int main()
{
	char* str = "{\"alg\":\"HS256\",\"typ\":\"JWT\"}";
	char* res = (char*)malloc(4 * (strlen(str) / 3) + 1);
	printf("res: %p\n", res);
	char* res2;

	printf("res2: %p\n", res2);
	int str_len = strlen(str);
	int res_len;

	printf("%s %d\n", str, strlen(str));

	base64eURL(str, res, str_len);
	printf("%s %d, max: %d\n", res, strlen(res), (4 * (strlen(str) / 3)) + 1);

	res_len = strlen(res);
	res2 = (char*)malloc(3 * (res_len / 4) + 1);
	printf("res2: %p\n", res2);

	base64dURL(res, res2, &res_len);
	printf("%s %d, max: %d\n", res2, strlen(res2), (3*(strlen(res)/4)+1));
	printf("res: %p\n", res);
	printf("res2: %p\n", res2);

	free(res);
	free(res2);


	return 0;
}
