#include <stdio.h>
#include <stdlib.h>

typedef struct _dllnode
{
    char data;
    struct _dllnode* next;
    struct _dllnode* prev;
}
dll;

// head of list
dll* head, *temp;

// insert proto
void Insert(char data);    

// print proto
void Print();

// print backward proto
void PrintBackward();

// destroy proto
void Destroy();
    
int main(int argc, char* argv[])
{    
    if( argc != 1)
    {
        printf("Usage: ./dll\n");
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
    PrintBackward();
    Destroy();
    fclose(fp);
    return 0;
}

void Insert(char data)
{
    // create new node
    dll* node = (dll *)malloc(sizeof(dll));
    
    // check for NULL
    if(node == NULL)
    {
        exit(1);
    }
    
    // initialize new node
    node->data = data;
    node->next = NULL;
    node->prev = NULL;
    
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
        node->prev = temp;
        temp = node;
    }
}

void Print()
{
    temp = head;
    printf("List is: \n");
    printf("HEAD <-> ");
    while(temp != NULL)
    {
        printf("%c <-> ", temp->data);

        // printf("%c | %p -> ", temp->data, temp->next);
        temp = temp->next;
    }
    printf("NULL\n");
}

void PrintBackward()
{
    temp = head;
    printf("List backward is: \n");
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    printf("NULL <-> ");
    while(temp->prev != NULL)
    {
        printf("%c <-> ", temp->data);
        temp = temp->prev;
    }
    printf("%c <-> ", temp->data);
    printf("HEAD\n");
}

void Destroy()
{
    while(head->next != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
    free(head);
}