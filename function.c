#include "main.h"

/* Remove leading zeros from a result list but keep one digit for value 0. */
void(remove_leading_zeros)(dlist** headr, dlist** tailr)
{
   dlist *temp = *headr;

    while (temp && temp->data == 0 && temp->next != NULL)
    {
        *headr = temp->next;
        (*headr)->prev = NULL;
        free(temp);
        temp = *headr;
    }
}

/* Compare magnitudes of two digit lists: 1 if list1>list2, -1 if list1<list2, 0 if equal. */
int compare_lists(dlist **head1, dlist **head2)
{
    dlist *temp1 = *head1;
    dlist *temp2 = *head2;

    while (temp1 && temp1->data == 0 && temp1->next != NULL)
    {
        temp1 = temp1->next;
    }

    while (temp2 && temp2->data == 0 && temp2->next != NULL)
    {
        temp2 = temp2->next;
    }

    int count1 = 0, count2 = 0;
    dlist *curr1 = temp1;
    dlist *curr2 = temp2;

    while (curr1)
    {
        count1++;
        curr1 = curr1->next;
    }

    while (curr2)
    {
        count2++;
        curr2 = curr2->next;
    }

    if (count1 > count2)
        return 1;
    if (count1 < count2)
        return -1;

    while (temp1 && temp2)
    {
        if (temp1->data > temp2->data)
            return 1;
        if (temp1->data < temp2->data)
            return -1;

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

/* Append a digit node at the tail of the list. */
int insert_last(dlist **head, dlist **tail, int data)
{
    dlist* new = malloc(sizeof(dlist));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail)->next = new;
        new->prev = *tail;
        *tail = new;
    }
    return SUCCESS;
}

/* Insert a digit node at the head of the list. */
int insert_first(dlist **head, dlist **tail, int data)
{
    dlist*new = malloc(sizeof(dlist));
    if(new == NULL)
    {
        return FAILURE;
    }
    new->data = data;
    new->next = NULL;
    new->prev = NULL;
    if(*head == NULL)
    {
        *head = new;
        *tail = new;
        return SUCCESS;
    }
    
    else
    {
        new->next = *head;
        new->next->prev = new;
        *head = new;
        return SUCCESS;
    
    }
    return FAILURE;
}

/* Print non-negative result in CLI format. */
void print_list(dlist *head,char *argv[])
{
    
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }

    printf(" Result of %s %c %s is : ",argv[1],argv[2][0],argv[3]);
    while (head)                                  
    {
        printf("%d", head -> data);                
        head = head -> next;
    }
    printf("\n");
    
}

/* Print negative result in CLI format. */
void neg_print_list(dlist *head,char *argv[])
{
    
    if (head == NULL)
    {
        printf("INFO : List is empty\n");
    }

    printf(" Result of %s %c %s is : -",argv[1],argv[2][0],argv[3]);
    while (head)                                  
    {
        printf("%d", head -> data);                
        head = head -> next;
    }
    printf("\n");
    
}


/* Free all nodes in a list and reset head/tail. */
int delete_list(dlist **head, dlist **tail)

{
    if(*head == NULL)
    {
        return FAILURE;
    }
    else
    {
        dlist*temp = *head;
        dlist*prev = NULL;
        while(temp)
        {
            prev = temp->next;
            free(temp);
            temp = prev;
        }
        *head = NULL;
        *tail = NULL;
        return SUCCESS;
    }
}
