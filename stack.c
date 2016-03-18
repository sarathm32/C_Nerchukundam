#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _snode
{
	char data;
	struct _snode* next;
}
stack;

// top, Rear, Temp of list
stack *top, *temp;

// Push proto
void Push(char data);

// Pop proto
void Pop(char data);

// Print proto
void Print();

// Destroy proto
void Destroy();

int main(int argc, char* argv[])
{
	if( argc != 1)
	{
		printf("Usage: ./stack\n");
		return -1;
	}

	// initialize lists
	top = NULL;
	temp = top;

	// open file
	FILE* fp = fopen("small", "r");
	if(fp == NULL)
	{
		printf("Error Opening File.\n");
		return 1;
	}

	for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
	{
		if(isalpha(c))
		{
			Push(c);
			Print();
		}
		else if( c == '\n' || c == '\0' || c == '\r')
		{
			continue;
		}
		else
		{
			Pop(c);
			Print();
		}
	}
	
	printf("\nFinal stack is: \n");
	Print();
	Destroy();
	fclose(fp);
	return 0;
}

void Push(char data)
{
	// create new node
	stack* node = (stack *)malloc(sizeof(stack));

	// check for NULL
	if(node == NULL)
	{
		exit(1);
	}

	// initialize new node
	node->data = data;
	node->next = NULL;

	// Push at first node
	if(top == NULL)
	{
		top = node;
	}
	// Push for all other nodes
	else
	{
		node->next = top;
		top = node;
	}
}

void Pop(char data)
{
	// create a temp node
	temp = top;
	if(top->next == NULL)
	{
		free(top);
	}
	else
	{
		top = top->next;
		free(temp);
	}
}

void Print()
{
	temp = top;
	printf("\nTOP\n");
	printf("---\n");
	while(temp != NULL)
	{
		printf("%c\n", temp->data);
		printf("---\n");
		temp = temp->next;
	}
	printf("BOTTOM\n\n");
}

void Destroy()
{
	while(top != NULL)
	{
		temp = top;
		top = top->next;
		free(temp);
		}
	free(top);
}