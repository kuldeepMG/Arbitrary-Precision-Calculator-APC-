#ifndef APC_H
#define APC_H

#define SUCCESS  0     // Operation successful
#define FAILURE -1     // Operation failed

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node structure for doubly linked list
typedef struct node
{
    int data;            // Store single digit
    struct node *prev;   // Pointer to previous node
    struct node *next;   // Pointer to next node
} node;

/* Function prototypes */

// Validate command-line inputs
int validate_inputs(char *argv[], int argc);

// Convert string number to linked list
int conv_str_to_list(node **head, node **tail, char *argv);

// Insert a node at the beginning
int insert_first(node **head, node **tail, int data);

// Insert a node at the end
int insert_last(node **head, node **tail, int data);

// Addition
void addition(node **head1, node **tail1,node **head2, node **tail2,node **headR, node **tailR);

// Compare two numbers: return 1 if first>second, 2 if second>first, 0 if equal
int is_greater(node **head1, node **tail1,node **head2, node **tail2);

// Subtraction
void subtraction(node **head1, node **tail1,node **head2, node **tail2,node **headR, node **tailR);

// Multiplication
void multiplication(node **head1, node **tail1,
                    node **head2, node **tail2,
                    node **headR, node **tailR);

// Remove leading zeros from result list
void remove_leading_zeros(node **head,node **tail);

// Delete first node of a linked list
int delete_first(node **head,node **tail);

// Delete entire linked list
int delete_list(node **head, node **tail);

// Division
void division(node **head1, node **tail1,
              node **head2, node **tail2,
              node **headR, node **tailR);

// Print linked list number
void print_list(node *head);

#endif
