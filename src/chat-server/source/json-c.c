#include "../header/json-c.h"

struct node** parseJSON(char* msg)
{

	struct node** hashTable = createHashTable();

#ifdef DEBUG
	printf("HastTable Created\n");
#endif

	int i = 0;
	
	char* key;

	char* ret_ptr;
	char* next_ptr;
	char* str = strdup(msg+1);
	char* ptrs = strchr(str, '}');

	*ptrs = '\0';

	ret_ptr = strtok_r(str, SEPS, &next_ptr);

	while(ret_ptr)
	{
		if(i%2 == 0)
		{
			key = strdup(ret_ptr);
		}
		else
		{
			insertData(&hashTable, getRawData(key), getRawData(ret_ptr));
			free(key);
		}

		ret_ptr = strtok_r(NULL, SEPS, &next_ptr);
		i++;
	}

	free(str);

	if(i % 2)
	{

		deleteHashTable(&hashTable);

		return (void*)0;
	}

	return hashTable;
}

void parseJSON_n(struct node*** hashTable, char* msg, int len)
{
	int i = 0, j = 0;
	
	char key[10];

	char* ret_ptr;
	char* next_ptr;

	char* str = getRawData(msg);
#ifdef DEBUG
	
#endif

	ret_ptr = strtok_r(str, SEPS, &next_ptr);

	while(ret_ptr)
	{
		if(i%2 == 0)
		{
			j = 0;
			while(ret_ptr[j+1] != '\0')
			{
				key[j] = ret_ptr[j+1];
				j++;
			}
			key[j-1] = '\0';
		}
		else
		{
		#ifdef DEBUG
			printf("Data / key: %s %d, value: %s %d\n", key, strlen(key), ret_ptr, strlen(ret_ptr));
		#endif

			insertData(hashTable, key, getRawData(ret_ptr));

		#ifdef DEBUG
			printf("Data inserted\n\n");
		#endif

		}

		ret_ptr = strtok_r(NULL, SEPS, &next_ptr);
		i++;
	}

	if(i % 2)
	{
//		cleanHashTable(hashTable);
	}

}

char* getRawData(char* str)
{
    str[strlen(str)-1] = '\0';

	return ++str;
}

char* createJSON(struct node*** hashTable)
{
	int i, j;
	int key_l, value_l;

	struct node* tmp;

	struct hashTable_in ht_in = getHashTableInfo(hashTable);

//	int ht_size = 2+(ht_in.nodeCount)+(ht_in.nodeCount*4)+(ht_in.nodeCount-1)+ht_in.strLength;
	int ht_size = 1+(ht_in.nodeCount*6)+ht_in.strLength;
	int cursor = 0;

	char* str = (char*)malloc(sizeof(char) * (ht_size + 1));
	*str = '\0';

	str[cursor++] = '{';


	for(i=0;i<TABLECAPA;i++)
	{
		tmp = *(*hashTable+i);

		if(tmp->key == NULL)
		{
			return (void*)0;
		}
		else
		{
			while(tmp)
			{
				key_l = strlen(tmp->key);
				value_l = strlen(tmp->value);

				str[cursor++] = '"';
				
				for(j=0;j<key_l;j++)
					str[cursor++] = tmp->key[j];

				str[cursor++] = '"';
				str[cursor++] = ':';
				str[cursor++] = '"';

				for(j=0;j<value_l;j++)
					str[cursor++] = tmp->value[j];

				str[cursor++] = '"';
				str[cursor++] = ',';

				tmp = tmp->nextPtr;

			}
		}
	}

	str[--cursor] = '}';
	cursor++;
	str[cursor] = '\0';

	printf("str: %s\n", str);

	deleteHashTable(hashTable);

	return str;
}
