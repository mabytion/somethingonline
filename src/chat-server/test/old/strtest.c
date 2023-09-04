#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getRawData(char* str)
{
	int i = strlen(str);
    str[i-1] = '\0';

    return ++str;
}

int main()
{
	char* test = malloc(sizeof(char) * 7);
	test[0] = '0';
	test[1] = '1';
	test[2] = '2';
	test[3] = '3';
	test[4] = '4';
	test[5] = '0';
	char* tmp;
	tmp = getRawData(test);

	printf("%s\n", tmp);

	free(test);

	return 0;
}
