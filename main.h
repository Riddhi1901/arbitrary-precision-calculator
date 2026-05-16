#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 0
#define FAILURE -1

/* Doubly linked list node storing a single decimal digit. */
typedef struct node
{
    struct node* prev;
    int data;
    struct node* next;
}dlist;

/* Utility helpers shared by arithmetic modules. */
void(remove_leading_zeros)(dlist** headr, dlist** tailr);
int compare_lists(dlist **head1, dlist **head2);

/* Core arithmetic operations on digit lists. */
int addition(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr);
int subtraction(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr);
int multiplication(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr);
int division(dlist **head1,dlist** tail1,dlist** head2,dlist** tail2,dlist** headr,dlist** tailr);

/* List insertion/printing/deallocation helpers. */
int insert_last(dlist **head, dlist **tail, int data);
int insert_first(dlist **head, dlist **tail, int data);
void print_list(dlist *head,char *argv[]);
void neg_print_list(dlist *head,char *argv[]);

int delete_list(dlist **head, dlist **tail);
