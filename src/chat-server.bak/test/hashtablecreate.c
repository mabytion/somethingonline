#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../header/hashtable.h"

int main(int argc, char** argv)
{
	struct node** hashTable;

	int i;

	for(i=0;i<100;i++)
	{
		hashTable = createHashTable();
		printf("## %d ## RESULT: %d\n\n", i+1, tableTest(&hashTable, i*300));
		deleteHashTable(&hashTable);
	}

	return 0;
}
