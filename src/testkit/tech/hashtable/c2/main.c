#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

int main(int argc, char** argv)
{
	struct node* hashTable;


	printf("createHashTable()\n");
	hashTable = createHashTable();
	printf("createHashTable-end-\n");

	int i;

	printTable(&hashTable);

	printf("\n");

	insertNode(&hashTable, createNode("1", "nomuhyun"));
	insertNode(&hashTable, createNode("2", "hyunmuno"));
	insertNode(&hashTable, createNode("3", "cantsee"));
	insertNode(&hashTable, createNode("4", "yuuuu"));
	insertNode(&hashTable, createNode("5", "555555555"));
	insertNode(&hashTable, createNode("6", "6666666"));
	insertNode(&hashTable, createNode("7", "77777777"));
	insertNode(&hashTable, createNode("8", "88888888"));
	insertNode(&hashTable, createNode("9", "999999999"));
	insertNode(&hashTable, createNode("10", "10101010101010"));
	insertNode(&hashTable, createNode("11", "11 11 11 11 11 11"));
	insertNode(&hashTable, createNode("12", "12 12 12 12 12 12 12 "));
	insertNode(&hashTable, createNode("13", "13 13 13 13 13 13 "));
	insertNode(&hashTable, createNode("14", "14 14 14 14 14 14 "));
	insertNode(&hashTable, createNode("15", "15 15 15 15 15 15 "));
	insertNode(&hashTable, createNode("16", "1616161616161616161616 "));
	insertNode(&hashTable, createNode("17", "17171717171717171717 "));
	insertNode(&hashTable, createNode("18", "18181818181818181818 "));
	insertNode(&hashTable, createNode("19", "19191919191919191919 "));
	insertNode(&hashTable, createNode("20", "202020202020202020 "));
	insertNode(&hashTable, createNode("21", "212121212121212121 "));
	insertNode(&hashTable, createNode("22", "22 22 22 22 22 22  "));
	insertNode(&hashTable, createNode("23", "232323232323232323 "));
	insertNode(&hashTable, createNode("24", "24242424242424242424 "));
	insertNode(&hashTable, createNode("25", "252525252525252525 "));
	insertNode(&hashTable, createNode("26", "26262626262626262626 "));
	insertNode(&hashTable, createNode("27", "27272727272727272727 "));
	insertNode(&hashTable, createNode("28", "282828282828282828 "));
	insertNode(&hashTable, createNode("29", "292929292929292929 "));
	insertNode(&hashTable, createNode("30", "303030303030303030 "));

	printTable(&hashTable);

	printf("\n");
	deleteNode(&hashTable, "2");
	deleteNode(&hashTable, "19");
	deleteNode(&hashTable, "31");
	deleteNode(&hashTable, "1");
	deleteNode(&hashTable, "17");
	deleteNode(&hashTable, "21");
	printf("\n");

	printTable(&hashTable);

	printf("2222222222222222222222222222222222222222222222222\n");
	deleteTable(&hashTable);
	printTable(&hashTable);


	return 0;
}
