#include "main.h"

/* Multiply two numbers represented as digit lists using partial products. */
int multiplication(dlist **head1, dlist **tail1,dlist **head2, dlist **tail2,dlist **headr, dlist **tailr)
{
    dlist *temp2 = *tail2;
    int count = 0;

    /* Running accumulated result. */
    dlist *headR1 = NULL, *tailR1 = NULL;

    while (temp2 != NULL)
    {
        dlist *temp1 = *tail1;
        /* Current partial product for one digit of multiplier. */
        dlist *headR2 = NULL, *tailR2 = NULL;
        int carry = 0;

        /* Shift partial product by appending zeros at the end position. */
        for (int i = 0; i < count; i++)
            insert_first(&headR2, &tailR2, 0);

        while (temp1 != NULL)
        {
            int sum = temp1->data * temp2->data + carry;
            carry = sum / 10;

            if (count == 0)
                insert_first(&headR1, &tailR1, sum % 10);
            else
                insert_first(&headR2, &tailR2, sum % 10);

            temp1 = temp1->prev;
        }

        /* Insert leftover carry for current partial multiplication. */
        if (carry != 0)
        {
            if (count == 0)
            {
                insert_first(&headR1, &tailR1, carry);
            }
            else
            {
                insert_first(&headR2, &tailR2, carry);
            }
        }

        if (count >= 1)
        {
            /* Accumulate previous result and new partial product. */
            dlist *headR = NULL, *tailR = NULL;

            addition(&headR1, &tailR1,&headR2, &tailR2,&headR, &tailR);

            headR1 = headR;
            tailR1 = tailR;

            delete_list(&headR2, &tailR2);
            headR = NULL;
            tailR = NULL;

        }

        temp2 = temp2->prev;
        count++;
    }

    /* Handle multiplication by zero. */
    if (headR1 == NULL)
        insert_first(&headR1, &tailR1, 0);

    *headr = headR1;
    *tailr = tailR1;

    return SUCCESS;
}
