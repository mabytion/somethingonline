#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef TABLECAPA
#define TABLECAPA 10
#endif

#ifndef __hashtable__
#define __hashtable__


struct node
{
	char* key;
	char* value;
	struct node* nextPtr;
};

struct hashTable_in
{
	int nodeCount;
	int strLength;
};

struct node** createHashTable();
struct node* createNode(const char*, const char*);
struct node* findNode(struct node***, const char*);
char* getValuebyKey(struct node***, const char*);
void insertNode(struct node***, struct node*);
void insertData(struct node***, const char*, const char*);
void deleteNode(struct node***, const char*);
void deleteHashTable(struct node***);
void cleanHashTable(struct node***);
void freeNode(struct node*);
void initNode(struct node*);
unsigned int ELFHash(const char*);
void peekNode(struct node*);
void printHashTable(struct node***);
struct hashTable_in getHashTableInfo(struct node***);

int tableTest(struct node***, int);
int intLength(int);
char* itoa(int);


#endif
