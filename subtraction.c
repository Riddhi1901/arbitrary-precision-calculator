#include "main.h"

/* Subtract second digit-list number from first and store result in headr/tailr. */
int subtraction(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr)
{
    dlist *temp1 = *tail1;
    dlist *temp2 = *tail2;
    int digit = 0;
    int borrow = 0;

    while(temp1 != NULL || temp2 != NULL)
    {
        /* Subtract from least significant digit (tail) towards head. */
        if(temp1 != NULL && temp2 != NULL)
        {
            digit = temp1->data - temp2->data - borrow;
            temp1 = temp1->prev;
            temp2 = temp2->prev;
        }
        else if( temp1 != NULL && temp2 == NULL)
        {
            digit = temp1 ->data - borrow;
            temp1 = temp1->prev;
        }
        else if(temp2 != NULL && temp1 == NULL)
        {
            digit =  0 - temp2 ->data - borrow;
            temp2 = temp2->prev;   
        }
        else{
            return FAILURE;
        }
        if(digit < 0)
        {
            /* Borrow from next higher digit. */
            digit += 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }
        
        if (insert_first(headr,tailr,digit) == FAILURE)
        {
            return FAILURE;
        }
    }

    /* Caller handles sign and leading-zero normalization. */
    return SUCCESS;
}
