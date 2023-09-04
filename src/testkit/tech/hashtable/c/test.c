#include <stdio.h>
#include <string.h>

char* getRawData(char* str)
{
    *(str+(strlen(str)-1)) = '\0';

    str++;

	return str;
}

void main()
{
	char* str = "\"test\"";
	char* str2 = strdup(str);

	printf("%s\n", str2);
	printf("%s\n", getRawData(str2));
}
