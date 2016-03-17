//queue

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct _qnode
{
    char data;
    struct _qnode* next;
}
queue;

// Front, Rear, Temp of list
queue* front, *temp, *rear;

// Enqueue proto
void Enqueue(char data);

// Dequeue proto
void Dequeue(char data);

// Print proto
void Print();

// Destroy proto
void Destroy();

int main(int argc, char* argv[])
{
    if( argc != 1)
    {
    printf("Usage: ./queue\n");
    return -1;
    }
    
    // initialize lists
    front = NULL;
    rear = front;
    temp = front;
    
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
            Enqueue(c);
            Print();
        }
        else if( c == '\n' || c == '\0' || c == '\r')
        {
            continue;
        }
        else
        {
            Dequeue(c);
            Print();
        }
    }
    
    printf("Final Queue is: \n");
    Print();
    Destroy();
    fclose(fp);
    return 0;
}

void Enqueue(char data)
{
    // create new node
    queue* node = (queue *)malloc(sizeof(queue));
    
    // check for NULL
    if(node == NULL)
    {
        exit(1);
    }
    
    // initialize new node
    node->data = data;
    node->next = NULL;
    
    // Enqueue at first node
    if(front == NULL && rear == NULL)
    {
        front = node;
        rear = node;
    }
    // Enqueue for all other nodes
    else
    {
        rear->next = node;
        rear = node;
    }
}

void Dequeue(char data)
{
    // create a temp node
    temp = front;
    front = front->next;
    
    free(temp);

}

void Print()
{
    temp = front;
    printf("FRONT | ");
    while(temp != NULL)
    {
        printf("%c | ", temp->data);
    
        temp = temp->next;
    }
    printf("REAR\n");
}

void Destroy()
{
    while(front != NULL)
    {
        temp = front;
        front = front->next;
        free(temp);
    }
    free(front);
}