#include <stdio.h>
#include <stdlib.h>

typedef struct _sllnode
{
    char data;
    struct _sllnode* next;
}
sll;

// head of list
sll* head, *temp;

// insert proto
void Insert(char data);    

// print proto
void Print();

// destroy proto
void Destroy();
    
int main(int argc, char* argv[])
{    
    if( argc != 1)
    {
        printf("Usage: ./sll\n");
        return -1;
    }
    
    // initialize lists
    head = NULL;
    temp = head;
    
    // open file
    FILE* fp = fopen("small", "r");
    if(fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        if( c == '\n' || c == '\0' || c == '\r')
        {
            continue;
        }
        else
        {
            Insert(c);
        }
    }
    
    Print();
    Destroy();
    fclose(fp);
    return 0;
}

void Insert(char data)
{
    // create new node
    sll* node = (sll *)malloc(sizeof(sll));
    
    // check for NULL
    if(node == NULL)
    {
        exit(1);
    }
    
    // initialize new node
    node->data = data;
    node->next = NULL;
    
    // insert at first node
    if(head == NULL)
    {
        head = node;
        temp = node;
    }
    // insert for all other nodes
    else
    {
        temp->next = node;
        temp = node;
    }
}

void Print()
{
    temp = head;
    printf("List is: ");
    while(temp != NULL)
    {
        printf("%c-> ", temp->data);

        // printf("%c | %p -> ", temp->data, temp->next);
        temp = temp->next;
    }
    printf("NULL\n");
}

void Destroy()
{
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
}