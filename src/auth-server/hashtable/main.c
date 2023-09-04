#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main(int argc, char** argv)
{
	struct node** hashTable;

	hashTable = createHashTable();

	int i;

	printTable(&hashTable);

	printf("\n");
	insertData(&hashTable, "1", "111111111111");
	insertData(&hashTable, "2", "111111111111");
	insertData(&hashTable, "18", "111111111111");
	insertData(&hashTable, "22", "22222");
	insertData(&hashTable, "21", "111111111111");
	insertData(&hashTable, "20", "111111111111");
	insertData(&hashTable, "17", "111111111111");
	insertData(&hashTable, "31", "111111111111");


	printTable(&hashTable);

	printf("\n");

	
	printf("findValue: %s\n", getValuebyKey(&hashTable, "22"));


	deleteNode(&hashTable, "2");
	deleteNode(&hashTable, "19");
	deleteNode(&hashTable, "31");
	deleteNode(&hashTable, "1");
	deleteNode(&hashTable, "17");
	deleteNode(&hashTable, "21");
	printf("\n");

	for(i=0;i<10;i++)
		printf("## %d ## RESULT: %d\n\n", i+1, tableTest(&hashTable, 1000));

	printTable(&hashTable);

	deleteTable(&hashTable);
	printTable(&hashTable);


	return 0;
}
