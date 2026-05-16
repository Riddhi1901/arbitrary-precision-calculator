#include "main.h"

/* Check whether a digit list represents numeric zero. */
int is_zero_list(dlist *head)
{
    if (head == NULL)
    {
        return 1;
    }

    while (head)
    {
        if (head->data != 0)
        {
            return 0;
        }
        head = head->next;
    }
    return 1;
}

/* Integer division by repeated subtraction: quotient only, no remainder output. */
int division(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr)
{
    /* Normalize operands before comparisons/subtractions. */
    remove_leading_zeros(head1,tail1);
    remove_leading_zeros(head2,tail2);

    /* Guard against divide-by-zero. */
    if (is_zero_list(*head2))
    {
        printf("Division by zero is not allowed\n");
        return FAILURE;
    }

    int count = 0;
    /* If divisor is larger, quotient is zero. */
    if(compare_lists(head1, head2) < 0)
    {
        insert_first(headr, tailr, 0);
        return SUCCESS;
    }

   /* Repeatedly subtract divisor from dividend and count iterations. */
   while (compare_lists(head1, head2) >= 0)
    {
        dlist *temph = NULL, *tempt = NULL;

        if (subtraction(head1, tail1,head2, tail2,&temph, &tempt) == FAILURE)
        {
            return FAILURE;
        }

        delete_list(head1, tail1);

        *head1 = temph;
        *tail1 = tempt;

        count++;
    }

    /* Convert integer count into quotient digit list. */
    if (count == 0)
    {
        insert_first(headr, tailr, 0);
    }
    else
    {
        while (count > 0)
        {
            insert_first(headr, tailr, count % 10);
            count = count / 10;
        }
    }

    return SUCCESS;
}
