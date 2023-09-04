#include "../header/hashtable.h"

struct node emptyNode = {"err", "not exist", NULL};

struct node** createHashTable()
{
	int i;
	struct node** hashTable = (struct node**)malloc(TABLECAPA * sizeof(struct node*));

	for(i=0;i<TABLECAPA;i++)
	{
		*(hashTable+i) = (void*)0;
	}

	return hashTable;
}

struct node* createNode(const char* key, const char* data)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));

	int keyLen = strlen(key);
	int dataLen = strlen(data);
	int i;

	for(i=0;i<keyLen;i++)
		newNode->key[i] = key[i];
	newNode->key[keyLen] = '\0';
	
	for(i=0;i<dataLen;i++)
		newNode->value[i] = data[i];
	newNode->value[dataLen] = '\0';
	
	newNode->nextPtr = NULL;

	return newNode;
}

struct node* findNode(struct node*** hashTable, const char* key)
{
	unsigned int index = ELFHash(key) % TABLECAPA;
	struct node* tmp = *(*hashTable+index);

	if(tmp == NULL)
	{
		return &emptyNode;
	}
	else
	{
		do
		{
			if(strcmp(key, tmp->key) == 0)
			{
				return tmp;
			}

			tmp = tmp->nextPtr;
		}while(tmp);

	}

	return &emptyNode;
}

char* getValuebyKey(struct node*** hashTable, const char* key)
{
	struct node* tmp;
	tmp = findNode(hashTable, key);

	return tmp->value;
}

void insertNode(struct node*** hashTable, struct node* dataNode)
{
	unsigned int index = ELFHash(dataNode->key) % TABLECAPA;

	struct node** tmp = (*hashTable)+index;
	struct node* tmp2 = *tmp;

	if(*tmp == NULL)
	{
		*tmp = dataNode;
	}
	else
	{
		while(tmp2->nextPtr)
		{
			tmp2 = tmp2->nextPtr;
		}

		tmp2->nextPtr = dataNode;
	}

}

void insertData(struct node*** hashTable, const char* key, const char* value)
{
	insertNode(hashTable, createNode(key, value));
}

void deleteNode(struct node*** hashTable, const char* key)
{
	unsigned int index = ELFHash(key) % TABLECAPA;
	struct node* prevNode = NULL;
	struct node** tmp = *hashTable+index;
	struct node* tmp2 = *tmp;

	struct node orig = *tmp2;

	if(tmp == NULL)
	{
		printf("err: deleteNode / Data Not Exists\n");
	}
	else
	{
		do
		{
			if(strcmp(key, tmp2->key) == 0)
			{
				if(prevNode == NULL)
				{
					if(tmp2->nextPtr)
					{
						freeNode(tmp2);
						*(*hashTable+index) = orig.nextPtr;
					}
					else
					{
						freeNode(*tmp);
						*tmp = NULL;
					}

				}
				else
				{
					prevNode->nextPtr = tmp2->nextPtr;
					freeNode(tmp2);
				}


				return;
			}
			else
			{
				prevNode = tmp2;
				tmp2 = tmp2->nextPtr;
			}


		}while(tmp2);

		printf("Node Not Found\n");
	}
	
}

void deleteHashTable(struct node*** hashTable)
{
	int i;
	struct node* prevNode;
	struct node* tmp;

	for(i=0;i<TABLECAPA;i++)
	{
		tmp = *(*hashTable+i);
		if(tmp == NULL)
		{
			
		}
		else
		{
			if(tmp->nextPtr == NULL)
			{
				freeNode(tmp);
			}
			else
			{
				while(tmp->nextPtr)
				{	
					prevNode = tmp;
					tmp = tmp->nextPtr;
					freeNode(prevNode);
				}

				freeNode(tmp);
			}
		}

		*(*hashTable+i) = NULL;
	}

	free(*hashTable);
}

void cleanHashTable(struct node*** hashTable)
{
	int i;
	struct node* prevNode;
	struct node* tmp;

	for(i=0;i<TABLECAPA;i++)
	{
		if(*(*(hashTable)+i) == NULL)
		{
			
		}
		else
		{
			tmp = *(*hashTable+i);
			if(tmp->nextPtr == NULL)
			{
				freeNode(tmp);
				free(tmp);
				*(*hashTable+i) = NULL;
			}
			else
			{
				while(tmp)
				{	
					prevNode = tmp;
					tmp = tmp->nextPtr;
					freeNode(prevNode);
					free(prevNode);
				}

			}
		}
		*(*hashTable+i) = NULL;
	}

}

void freeNode(struct node* dataNode)
{
//	free(dataNode->key);
//	free(dataNode->value);
	dataNode->nextPtr = (void*)0;

//	free(dataNode);
}

void initNode(struct node* dataNode)
{
	int i;

	for(i=0;i<10;i++)
		dataNode->key[i] = '\0';

	for(i=0;i<10;i++)
		dataNode->value[i] = '\0';

	dataNode->nextPtr = (void*)0;
}

unsigned int ELFHash(const char* str)
{
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;

	while(*str)
	{
		hash = (hash << 4) + (*str);

		if((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
			hash &= ~x;
		}
		str++;
	}

	return (hash & 0x7FFFFFFFL);
}

void peekNode(struct node* dataNode)
{
	if(dataNode)
	{
		printf("key: %s\n", dataNode->key);
		printf("value: %s\n", dataNode->value);
		printf("nextPtr: %p\n", dataNode->nextPtr);
	}
	else
	{
		printf("DataNode is NULL\n");
	}
}

void printHashTable(struct node*** hashTable)
{
	struct node* tmp;
	int i;
	int j;

	for(i=0;i<TABLECAPA;i++)
	{
		j = 0;
		printf("[%d][%d] ", i, j);
		tmp = *(*hashTable+i);
		if(tmp == NULL)
		{
			printf("(nil), Ptr: %p\n", tmp);
		}
		else
		{
			printf("key: %s, value: %s, nextPtr: %p, Ptr: %p\n", tmp->key, tmp->value, tmp->nextPtr, tmp);
			while(tmp->nextPtr)
			{
				j++;
				tmp = tmp->nextPtr;
				printf(" - [%d][%d] ", i, j);
				printf("key: %s, value: %s, nextPtr: %p, Ptr: %p\n", tmp->key, tmp->value, tmp->nextPtr, tmp);
			}
		}
	}
}

struct hashTable_in getHashTableInfo(struct node*** hashTable)
{
	struct node* tmp;
	struct hashTable_in ht_in;
	int i;
	int nodeCount = 0;
	int strLength = 0;

	for(i=0;i<TABLECAPA;i++)
	{
		tmp = *(*hashTable+i);

		if(tmp == NULL)
		{

		}
		else
		{
			while(tmp)
			{
				nodeCount++;
				strLength += strlen(tmp->key);
				strLength += strlen(tmp->value);
				tmp = tmp->nextPtr;
				
			}
		}
	}

	ht_in.nodeCount = nodeCount;
	ht_in.strLength = strLength;

//	return 2+(nodeCount)+(nodeCount*4)+(nodeCount-1)+strLength;
	return ht_in;
}

int tableTest(struct node*** hashTable, int cycle)
{
    int i;
	char* str;
	char* str2;
	struct hashTable_in ht_in;

	if(cycle < 1)
	{
		return -1;
	}
	
	printf("TEST Start: insertData / range: 1-%d\n", cycle);

	for(i=1;i<=cycle;i++)
	{
		str = itoa(i);

		if(i%(cycle/2) == 0)
			printf("%d/%d [%d\%] Processing.... ", i, cycle, i*100/cycle);

		insertData(hashTable, str, str);

		if(i%(cycle/2) == 0)
			printf("Done.\n");
	}
	printf("TEST End: insertData\n");

//	printHashTable(hashTable);
	ht_in = getHashTableInfo(hashTable);
	printf("Node Count: %d, String Length: %d\n", ht_in.nodeCount, ht_in.strLength);

	printf("TEST Start: deleteNode / range: 1-%d\n", cycle);
	for(i=1;i<=cycle;i++)
	{
		str2 = itoa(i);
		if(i%(cycle/2) == 0)
			printf("%d/%d [%d\%] Processing.... ", i, cycle, i*100/cycle);

		deleteNode(hashTable, str2);

		if(i%(cycle/2) == 0)
			printf("Done.\n");
	}
	printf("TEST End: deleteNode\n");

//	printHashTable(hashTable);
	ht_in = getHashTableInfo(hashTable);
	printf("Node Count: %d, String Length: %d\n", ht_in.nodeCount, ht_in.strLength);

	free(str);
	free(str2);

	return 0;
}

int intLength(int num)
{
	int len = 0;

	if(num < 0)
	{
		len++;
	}

	while(num)
	{
		len++;
		num /= 10;
	}

	return len;
}

char* itoa(int num)
{
	char *str;
	int i;
	long long value;
	long long div;

	if(num == 0)
		return 0;

	i = 0;
	div = 1;
	value = num;
	str = (char*)malloc(sizeof(char) * (intLength(num) + 1));

	while(value / div)
	{
		div *= 10;
	}

	div /= 10;

	if(value < 0)
	{
		str[i++] = '-';
		value *= -1;
	}

	while(div)
	{
		str[i++] = value / div + 48;
		value %= div;
		div /= 10;
	}
	str[i] = '\0';

	return str;
	
}    
