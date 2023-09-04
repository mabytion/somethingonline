#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

#ifndef SEPS
#define SEPS ":,"
#endif

#ifndef __jsonc__
#define __jsonc__

struct node** parseJSON(char*);
void parseJSON_n(struct node***, char*, int);
char* getRawData(char *);
char* createJSON(struct node***);


#endif
