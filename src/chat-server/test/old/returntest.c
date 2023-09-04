#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* test = "test";

char* testfunc(int i)
{
	char* tmp;

	if(i)
		tmp = strdup(test);
	else
		return (void*)0;

	return tmp;
}

int main()
{
	char* tests = (void*)0;
	char* tests2 = "abc";
//	printf("%s %s\n", tests, tests2);
//	printf("%s %s\n", testfunc(1), testfunc(0));
//	printf("%s %s\n", tests = testfunc(1), tests2 = testfunc(0));
//	printf("%s %s\n", tests, tests2);

	if(tests2 = testfunc(0))
		printf("oh\n");
	else
		printf("zzz\n");

	if(tests2 = testfunc(1))
		printf("tests2: %s\n", tests2);
	else
		printf("zzzzzzzzzz\n");

	return 0;
}
