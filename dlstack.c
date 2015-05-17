#include<stdio.h>
#include<stdlib.h>

typedef struct Node 
{
        int data;
        struct Node *next;
        struct Node *prev;
}node;

void insert(node *pointer, int data)
{
        /* Iterate through the list till we encounter the last node.*/
        while(pointer->next!=NULL)
        {
                pointer = pointer -> next;
        }
        /* Allocate memory for the new node and put data in it.*/
        pointer->next = (node *)malloc(sizeof(node));
        (pointer->next)->prev = pointer;
        pointer = pointer->next;
        pointer->data = data;
        pointer->next = NULL;
}

int find(node *pointer, int key)
{
	node *temp=pointer;
        temp= temp -> next;
        /* Iterate through the entire linked list and search for the key. */
        while(temp!=NULL)
        {
                if(temp->data == key) //key is found.
                {
                        return 1;
                }
                temp = temp -> next;//Search in the next node.
        }
        /*Key is not found */
        return 0;
}

void delete(node *pointer, int data)
{
        /* Go to the node for which the node next to it has to be deleted */
        while(pointer->next!=NULL && (pointer->next)->data != data)
        {
                pointer = pointer -> next;
        }
        if(pointer->next==NULL)
        {
                printf("Element %d is not present in the list\n",data);
                return;
        }
        /* Now pointer points to a node and the node next to it has to be removed */
        node *temp;
        temp = pointer -> next;
        /*temp points to the node which has to be removed*/
        pointer->next = temp->next;
        temp->prev =  pointer;
        /*We removed the node which is next to the pointer (which is also temp) */
        free(temp);
        /* Beacuse we deleted the node, we no longer require the memory used for it . 
           free() will deallocate the memory.
         */
        return;
}

void print(node *pointer)
{
        if(pointer==NULL)
        {
                return;
        }
        printf("%d ",pointer->data);
        print(pointer->next);
}

int main()
{
        node *head,*temp;
        head = (node *)malloc(sizeof(node)); 
        head-> next = NULL;
        head-> prev = NULL;
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Print\n");
        printf("4. Find\n");
        printf("5. Exit\n");
        int query;
        scanf("%d",&query);
        while(query!=5)
        {
                if(query==1)
                {
                        int data;
                        scanf("%d",&data);
                        insert(head,data);
                }
                else if(query==2)
                {
                        int data;
                        scanf("%d",&data);
                        delete(head,data);
                }
                else if(query==3)
                {
                        printf("The list is ");
                        print(head->next);
                        printf("\n");
                }
                else if(query==4)
                {
                        int data;
                        scanf("%d",&data);
                        int status = find(head,data);
                        if(status)
                        {
                                printf("Element Found\n");
                        }
                        else
                        {
                                printf("Element Not Found\n");

                        }
                }
        }


}


