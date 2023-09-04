#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef __hashtable__
#define __hashtable__


struct node
{
	char* key;
	char* value;
	struct node* nextPtr;
};

struct node* createHashTable();
struct node* createNode(const char*, const char*);
struct node* findNode(struct node**, const char*);
void insertNode(struct node**, struct node*);
void deleteNode(struct node**, const char*);
void deleteTable(struct node**);
void freeNode(struct node*);
unsigned int ELFHash(const char*);
void peekNode(struct node*);
void printTable(struct node**);
char* getValue(struct node*);

#endif

#ifndef TABLECAPA
#define TABLECAPA 10
#endif
