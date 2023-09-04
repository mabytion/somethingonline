#include "hashtable.h"

struct node emptyNode = {"err", "not exist", NULL};

struct node* createHashTable()
{
	int i;
	struct node* hashTable = (struct node*)malloc(TABLECAPA * sizeof(struct node));
	memset(hashTable, 0, TABLECAPA * sizeof(struct node));
	
	printf("new Table: %p\n", hashTable);

	return hashTable;
}

struct node* createNode(const char* key, const char* data)
{
	struct node* newNode = malloc(sizeof(struct node));
	newNode->key = strdup(key);
	newNode->value = strdup(data);
	newNode->nextPtr = NULL;
	
	return newNode;
}

struct node* findNode(struct node** hashTable, const char* key)
{
	unsigned int index = ELFHash(key) % TABLECAPA;
	struct node* tmp = *hashTable+index;

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
		}while(tmp->nextPtr);

	}

	return &emptyNode;
}

void insertNode(struct node** hashTable, struct node* dataNode)
{
	unsigned int index = ELFHash(dataNode->key) % TABLECAPA;
	struct node* tmp = *hashTable+index;

	if(tmp == 0)
	{
		tmp = dataNode;
	}
	else
	{
		while(tmp->nextPtr)
		{
			tmp = tmp->nextPtr;
		}

		tmp->nextPtr = dataNode;
	}

}

void deleteNode(struct node** hashTable, const char* key)
{
	unsigned int index = ELFHash(key) % TABLECAPA;
	struct node* prevNode = NULL;
	struct node* tmp = *hashTable+index;

	if(tmp == NULL)
	{
		printf("err: deleteNode / Not Exists");
	}
	else
	{
		do
		{
			if(strcmp(key, tmp->key) == 0)
			{
				if(prevNode == NULL)
				{
					if(tmp->nextPtr)
					{
						prevNode = tmp->nextPtr;
						freeNode(tmp);
						tmp = prevNode;
					}
					else
					{
						freeNode(tmp);
						tmp = NULL;
					}

				}
				else
				{
					prevNode->nextPtr = tmp->nextPtr;
					freeNode(tmp);
				}

				return;
			}
			else
			{
				prevNode = tmp;
				tmp = tmp->nextPtr;
			}


		}while(tmp->nextPtr);

		printf("Node Not Found\n");
	}
	
}

void deleteTable(struct node** hashTable)
{
	int i;

	for(i=0;i<TABLECAPA;i++)
	{
		printf("[%d] [%p]free\n", i, *hashTable+i);
		if(i==0)
			free(*hashTable+i);
	}
}

void freeNode(struct node* dataNode)
{
	printf("[ F R E E ]\n");
	peekNode(dataNode);
	free(dataNode->key);
	free(dataNode->value);
	dataNode->nextPtr = NULL;

	free(dataNode);
	peekNode(dataNode);
	printf("[ C O M P L E T E ]\n");
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

void printTable(struct node** hashTable)
{
	struct node* tmp;
	int i;
	int j;

	for(i=0;i<TABLECAPA;i++)
	{
		j = 0;
		printf("[%d][%d] ", i, j);
		tmp = *hashTable+i;
		if(tmp == NULL)
		{
			printf("(nil), Ptr: %p\n", tmp);
		}
		else
		{
			printf("key: %s, value: %s, nextPtr: %x, Ptr: %p\n", tmp->key, tmp->value, tmp->nextPtr, tmp);
			while(tmp->nextPtr)
			{
				j++;
				tmp = tmp->nextPtr;
				printf(" - [%d][%d] ", i, j);
				printf("key: %s, value: %s, nextPtr: %x, Ptr: %p\n", tmp->key, tmp->value, tmp->nextPtr, tmp);
			}
		}
	}
}
