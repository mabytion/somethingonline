#include <stdio.h>
#include <stdlib.h>

struct node
{
	char* key;
	char* value;
	struct node* nextPtr;
};

int main()
{
	struct node** test = NULL;
	int i;
	
	for(i=0;i<10;i++)
	{
		printf("%p\n", test);
		test = (struct node**)malloc(10 * sizeof(struct node*)); 
		printf("%p\n", test);
		free(test);
		test = NULL;
	}

	return 0;
}
