#include "main.h"

/* Add two numbers represented as digit lists and store result in headr/tailr. */
 int addition(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr)
 {
    dlist *temp1 = *tail1;
    dlist *temp2 = *tail2;
    int sum = 0;
    int carry = 0;

    while(temp1 != NULL || temp2 != NULL)
    {
        /* Add from least significant digit (tail) to most significant digit. */
        if(temp1 != NULL && temp2 != NULL)
        {
            sum = temp1->data + temp2->data + carry;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if( temp1 != NULL && temp2 == NULL)
        {
            sum = temp1 ->data + carry;
            temp1 = temp1->prev;
        }
        else if(temp2 != NULL && temp1 == NULL)
        {
            sum = temp2 ->data + carry;
            temp2 = temp2->prev;   
        }
        else{
            return FAILURE;
        }
        carry = sum/10;
        sum = sum%10;
        /* Push computed digit at front since we are traversing backwards. */
        insert_first(headr,tailr,sum);
    }

    /* Add leftover carry if present. */
    if(carry)
    {
        insert_first(headr,tailr,carry);
    }
    return SUCCESS;

 }
