/* Project Name : Arbitrary Precision Calculator (APC)
   Name   : Riddhi Balaji Shitole (25034F_036)
Description : This program implements an arbitrary precision calculator that can perform addition, subtraction, multiplication, 
            and division on large integers represented as doubly linked lists. The program takes two operands and an operator 
            as command-line arguments, processes the inputs, and outputs the result while handling edge cases such as negative 
            numbers and leading zeros. */
 

#include "main.h"

int convert_to_digits(dlist** head1,dlist** tail1,dlist** head2,dlist** tail2,char*argv[]);
/* Internal helper to check whether a list value is zero. */
static int list_is_zero(dlist *head);

int main(int argc,char* argv[])
{
    /* Main driver for big-integer operations using linked-list digits. */
    /* Separate input numbers and result as digit-wise doubly linked lists. */
    dlist* head1 = NULL;
    dlist* tail1 = NULL;

    dlist* head2 = NULL;
    dlist* tail2 = NULL;

    dlist* headr = NULL;
    dlist* tailr = NULL;

    /* Expected CLI usage: <num1> <operator> <num2>. */
    if(argc != 4)
    {
        printf("Arguments should be 4\n");
        return FAILURE;
    }
    /* Operator must be a single character (+, -, x, /). */
    if (strlen(argv[2]) != 1)
    {
        printf("ERROR: Invalid operator\n");
        return FAILURE;
    }
    /* Dispatch to arithmetic operation based on operator token. */
    switch(argv[2][0])
    {
            case '+':
            {
                    /* Parse both input strings into digit lists once for this operation. */
                    if(convert_to_digits(&head1,&tail1,&head2,&tail2,argv)== SUCCESS)
                    {
                        /* Sign-aware addition:
                           a) (-a) + (-b) => -(a+b)
                           b) (-a) + b    => b-a (or -(a-b))
                           c) a + (-b)    => a-b (or -(b-a))
                           d) a + b       => a+b */
                        if(argv[1][0] == '-' && argv[3][0] == '-') // both numbers are negative
                        {
                            if(addition(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                            {
                                remove_leading_zeros(&headr,&tailr);
                                neg_print_list(headr,argv);
                            }
                        }
                        else if(argv[1][0] == '-' && argv[3][0] != '-') // first number is negative and second number is positive
                        {
                            /* Compare absolute values to choose subtraction order/sign. */
                            int cmp = compare_lists(&head1, &head2);
                            if(cmp == 0)
                            {
                                printf(" Result of %s %c %s is : 0\n",argv[1],argv[2][0],argv[3]);
                                return SUCCESS;
                            }
                            if(cmp == 1)
                            {
                                if(subtraction(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                                {
                                    remove_leading_zeros(&headr,&tailr);
                                    neg_print_list(headr,argv);
                                }
                            }
                            else
                            {
                                if(subtraction(&head2,&tail2,&head1,&tail1,&headr,&tailr)== SUCCESS)
                                {
                                    remove_leading_zeros(&headr,&tailr);
                                    print_list(headr,argv);
                                }
                            }
                        }
                        else if(argv[1][0] != '-' && argv[3][0] == '-') // first number is positive and second number is negative
                        {
                            /* Compare absolute values to choose subtraction order/sign. */
                            int cmp = compare_lists(&head1, &head2);
                            if(cmp == 0)
                            {
                                printf(" Result of %s %c %s is : 0\n",argv[1],argv[2][0],argv[3]);
                                return SUCCESS;
                            }
                            if(cmp == 1)
                            {
                                if(subtraction(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                                {
                                    /* Trim leading zeros before printing final answer. */
                                    remove_leading_zeros(&headr,&tailr);
                                    print_list(headr,argv);
                                }
                            }
                            else
                            {
                                if(subtraction(&head2,&tail2,&head1,&tail1,&headr,&tailr)== SUCCESS)
                                {
                                    /* Trim leading zeros before printing final answer. */
                                    remove_leading_zeros(&headr,&tailr);
                                    neg_print_list(headr,argv);
                                }
                            }
                        }
                        else
                        {
                                if(addition(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS) //
                                {
                                    remove_leading_zeros(&headr,&tailr);
                                    print_list(headr,argv);
                                }
                            
                        }
                }
        }
        
            break;
            case '-':
            {
                if(convert_to_digits(&head1,&tail1,&head2,&tail2,argv)== SUCCESS)
                {
                    /* Sign-aware subtraction:
                       a) (-a) - b    => -(a+b)
                       b) a - (-b)    => a+b
                       c) (-a) - (-b) => b-a
                       d) a - b       => a-b */
                    if(argv[1][0] == '-' && argv[3][0] != '-')
                    {
                        if(addition(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            neg_print_list(headr,argv);
                        }
                    }
                    else if(argv[1][0] != '-' && argv[3][0] == '-')
                    {
                        if(addition(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            print_list(headr,argv);
                        }
                    }
                    else if(argv[1][0] == '-' && argv[3][0] == '-')
                    {
                        /* For (-a)-(-b), compare |a| and |b| to set sign/magnitude. */
                        int cmp = compare_lists(&head1, &head2);
                        if(cmp == 0)
                        {
                            printf(" Result of %s %c %s is : 0\n",argv[1],argv[2][0],argv[3]);
                            return SUCCESS;
                        }
                        if(cmp == 1)
                        {
                            if(subtraction(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                            {
                                remove_leading_zeros(&headr,&tailr);
                                neg_print_list(headr,argv);
                            }
                        }
                        else
                        {
                            if(subtraction(&head2,&tail2,&head1,&tail1,&headr,&tailr)== SUCCESS)
                            {
                                remove_leading_zeros(&headr,&tailr);
                                print_list(headr,argv);
                            }
                        }
                    }
                    else
                    {
                        /* For a-b, compare |a| and |b| to set sign/magnitude. */
                        int cmp = compare_lists(&head1, &head2);
                        if(cmp == 0)
                        {
                            printf(" Result of %s %c %s is : 0\n",argv[1],argv[2][0],argv[3]);
                            return SUCCESS;
                        }
                        if(cmp == 1)
                        {
                            if(subtraction(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                            {
                                remove_leading_zeros(&headr,&tailr);
                                print_list(headr,argv);
                            }
                        }
                        else
                        {
                            if(subtraction(&head2,&tail2,&head1,&tail1,&headr,&tailr)== SUCCESS)
                            {
                                remove_leading_zeros(&headr,&tailr);
                                neg_print_list(headr,argv);
                            }
                        }
                }
            }
            break;

            case 'x':
            {
                if(convert_to_digits(&head1,&tail1,&head2,&tail2,argv)== SUCCESS)
                {
                    /* Multiplication sign rules:
                       same signs => positive, different signs => negative. */
                    if(argv[1][0] == '-' && argv[3][0] == '-')
                    {
                        if(multiplication(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            print_list(headr,argv);
                        }
                    }
                    else if(argv[1][0] == '-' && argv[3][0] != '-')
                    {
                        if(multiplication(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            neg_print_list(headr,argv);
                        }
                    }
                    else if(argv[1][0] != '-' && argv[3][0] == '-')
                    {
                        if(multiplication(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            neg_print_list(headr,argv);
                        }
                    }
                    else
                    {
                        if(multiplication(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            print_list(headr,argv);
                        }  
                    }
                }
            }
            break;

            case '/':
            {
                if(convert_to_digits(&head1,&tail1,&head2,&tail2,argv)== SUCCESS)
                {
                    /* Division sign rules:
                       same signs => positive, different signs => negative. */
                    if(argv[1][0] == '-' && argv[3][0] == '-')
                    {
                        if(division(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            print_list(headr,argv);
                        }
                    }
                    else if(argv[1][0] == '-' && argv[3][0] != '-')
                    {
                        if(division(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            neg_print_list(headr,argv);
                        }
                    }
                    else if(argv[1][0] != '-' && argv[3][0] == '-')
                    {
                        if(division(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            neg_print_list(headr,argv);
                        }
                    }
                    else
                    {
                        if(division(&head1,&tail1,&head2,&tail2,&headr,&tailr)== SUCCESS)
                        {
                            remove_leading_zeros(&headr,&tailr);
                            print_list(headr,argv);
                        }  
                    }
                }
            }
            break;
            default :
            {
                printf("invalid Argument\n");
            }
        }
    }
}

static int list_is_zero(dlist *head)
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

/* Parse argv operands into digit lists, skipping optional leading '-'. */
int convert_to_digits(dlist** head1,dlist** tail1,dlist** head2,dlist** tail2,char*argv[])
{
    int i = 0,j = 0;
    
    /* Skip optional '-' sign and push each digit of first operand into list-1. */
    if(argv[1][0] == '-')
    {
        i = 1;
        while(argv[1][i] != '\0')
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')   
            {
                int num = argv[1][i] - '0';       
                insert_last(head1, tail1, num);     
            }
            else
            {
                printf("It should be a number\n");
                return FAILURE;
            }
            i++;
        }
    }

    else
    {
        while(argv[1][i] != '\0')
        {
            if (argv[1][i] >= '0' && argv[1][i] <= '9')   
            {
                int num = argv[1][i] - '0';       
                insert_last(head1, tail1, num);     
            }
            else
            {
                printf("It should be a number\n");
                return FAILURE;
            }
            i++;
        }
    }

    /* Skip optional '-' sign and push each digit of second operand into list-2. */
    if(argv[3][0] == '-')
    {
        j = 1;
        while(argv[3][j] != '\0')
        {
            if (argv[3][j] >= '0' && argv[3][j] <= '9')   
            {
                int num = argv[3][j] - '0';       
                insert_last(head2, tail2, num);     
            }
            else
            {
                printf("It should be a number\n");
                return FAILURE;
            }
            j++;
        }
    }

    else
    {
        while(argv[3][j] != '\0')
        {
            if (argv[3][j] >= '0' && argv[3][j] <= '9')   
            {
                int num = argv[3][j] - '0';       
                insert_last(head2, tail2, num);     
            }
            else
            {
                printf("It should be a number\n");
                return FAILURE;
            }
            j++;
        }
    }
    return SUCCESS;
}
