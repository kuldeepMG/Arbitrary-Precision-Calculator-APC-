#include "apc.h"

/* Validate command line arguments */
int validate_inputs(char *argv[], int argc)
{
    if (argc != 4)                  // Should have exactly 3 arguments
        return FAILURE;

    int i;

    // Check first operand (allow leading '-')
    i = 0;
    if (argv[1][0] == '-')          // Skip minus if present
        i = 1;

    while (argv[1][i] != '\0')      // Check each character
    {
        if (!isdigit(argv[1][i]))
            return FAILURE;
        i++;
    }

    // Check second operand (allow leading '-')
    i = 0;
    if (argv[3][0] == '-')
        i = 1;

    while (argv[3][i] != '\0')
    {
        if (!isdigit(argv[3][i]))
            return FAILURE;
        i++;
    }

    // Check operator
    if (strcmp(argv[2], "+") == 0 || strcmp(argv[2], "-") == 0 ||
        strcmp(argv[2], "x") == 0 || strcmp(argv[2], "/") == 0)
        return SUCCESS;

    return FAILURE;
}

/* Convert and store string number into doubly linked list */
int conv_str_to_list(node **head, node **tail, char *argv)
{
    int i = 0;
    while (argv[i] != '\0')
    {
        if (insert_last(head, tail, argv[i] - '0') == FAILURE)  // Insert each digit
            return FAILURE;
        i++;
    }
    return SUCCESS;
}

/* Insert node at the end of list */
int insert_last(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));  // Allocate memory
    if (new == NULL)
        return FAILURE;

    new->data = data;                  // Store digit
    new->next = NULL;                  // Next is NULL
    new->prev = *tail;                 // Prev is old tail

    if (*head == NULL)                 // If list empty
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail)->next = new;           // Link old tail
        *tail = new;                   // Update tail
    }
    return SUCCESS;
}

/* Insert node at the beginning of list */
int insert_first(node **head, node **tail, int data)
{
    node *new = malloc(sizeof(node));  // Allocate memory
    if (new == NULL)
        return FAILURE;

    new->data = data;                  // Store digit
    new->prev = NULL;                  // No previous
    new->next = *head;                 // Next is old head

    if (*head == NULL)                 // If list empty
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*head)->prev = new;           // Link old head
        *head = new;                   // Update head
    }
    return SUCCESS;
}

/* Add two numbers stored in linked lists */
void addition(node **head1, node **tail1,
              node **head2, node **tail2,
              node **headR, node **tailR)
{
    int carry = 0, res = 0;
    int data1 = 0, data2 = 0;

    node *temp1 = *tail1;              // Start from least significant digit
    node *temp2 = *tail2;

    if (temp1 != NULL)
        data1 = temp1->data;
    if (temp2 != NULL)
        data2 = temp2->data;

    while (temp1 != NULL || temp2 != NULL)
    {
        res = data1 + data2 + carry;   // Add digits + carry
        carry = res / 10;              // Update carry
        res = res % 10;                // Store single digit

        insert_first(headR, tailR, res);  // Insert at front

        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
            if (temp1 != NULL)
                data1 = temp1->data;
            else
                data1 = 0;
        }
        else
            data1 = 0;

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
            if (temp2 != NULL)
                data2 = temp2->data;
            else
                data2 = 0;
        }
        else
            data2 = 0;
    }

    if (carry != 0)
        insert_first(headR, tailR, carry); // Remaining carry
}

/* Compare two numbers: 1=first>second, 2=second>first, 0=equal */
int is_greater(node **head1, node **tail1,
               node **head2, node **tail2)
{
    node *temp1 = *head1;
    node *temp2 = *head2;
    int count1 = 0, count2 = 0;

    while (temp1 != NULL) 
    { 
        count1++; 
        temp1 = temp1->next; 
    }
    while (temp2 != NULL) 
    { 
        count2++; 
        temp2 = temp2->next; 
    }

    if (count1 > count2) return 1;
    if (count1 < count2) return 2;

    //if count1 = count2
    temp1 = *head1; //reset temp
    temp2 = *head2;

    while (temp1 != NULL)
    {
        if (temp1->data > temp2->data) return 1;
        if (temp1->data < temp2->data) return 2;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    return 0; // Equal numbers
}

/* Subtract second number from first */
void subtraction(node **head1, node **tail1,
                 node **head2, node **tail2,
                 node **headR, node **tailR)
{
    int rec = is_greater(head1, tail1, head2, tail2); 
    int borrow = 0, res = 0;

    node *temp1 = *tail1;
    node *temp2 = *tail2;

    if (rec == 2)
    {
        //swap
        temp1 = *tail2; 
        temp2 = *tail1;
    }

    int data1 = 0, data2 = 0;
    if (temp1 != NULL) 
        data1 = temp1->data;
    if (temp2 != NULL) 
        data2 = temp2->data;

    while (temp1 != NULL || temp2 != NULL)
    {
        if (borrow != 0)
        {
            data1--;
            borrow = 0;
        }

        if (data1 < data2)
        {
            data1 =data1 + 10;
            borrow = 1;
        }

        res = data1 - data2;
        insert_first(headR, tailR, res);

        if (temp1 != NULL)
        {
            temp1 = temp1->prev;
            if (temp1 != NULL)
                data1 = temp1->data;
            else
                data1 = 0;
        }
        else
            data1 = 0;

        if (temp2 != NULL)
        {
            temp2 = temp2->prev;
            if (temp2 != NULL)
                data2 = temp2->data;
            else
                data2 = 0;
        }
        else
            data2 = 0;
    }

    remove_leading_zeros(headR, tailR); // Remove leading zeros
}

/* Delete first node */
int delete_first(node **head, node **tail)
{
    if (*head == NULL)
        return FAILURE;

    if (*head == *tail)
    {
        free(*head);
        *head = *tail = NULL;
        return SUCCESS;
    }

    node *temp = *head;
    *head = temp->next;
    (*head)->prev = NULL;
    free(temp);
    return SUCCESS;
}

/* Delete entire linked list */
int delete_list(node **head, node **tail)
{
    if (*head == NULL)
        return FAILURE;

    node *temp = *head;
    while (temp != NULL)
    {
        *head = temp->next;
        free(temp);
        temp = *head;
        if (temp != NULL)
            temp->prev = NULL;
    }

    *tail = NULL;
    return SUCCESS;
}

/* Remove leading zeros */
void remove_leading_zeros(node **head, node **tail)
{
    while (*head != NULL && (*head)->data == 0)
        delete_first(head, tail);
}

/* Multiply two numbers */
void multiplication(node **head1, node **tail1,
                    node **head2, node **tail2,
                    node **headR, node **tailR)
{
    node *t2 = *tail2;
    int shift = 0;
    *headR = *tailR = NULL;

    while (t2 != NULL)
    {
        node *t1 = *tail1;
        node *headTemp = NULL, *tailTemp = NULL;
        int carry = 0;

        while (t1 != NULL)
        {
            int res = t1->data * t2->data + carry;
            carry = res / 10;
            insert_first(&headTemp, &tailTemp, res % 10);
            t1 = t1->prev;
        }

        if (carry != 0)
            insert_first(&headTemp, &tailTemp, carry);

        int i;
        for (i = 0; i < shift; i++)
            insert_last(&headTemp, &tailTemp, 0);

        addition(&headTemp, &tailTemp, headR, tailR, headR, tailR);
        delete_list(&headTemp, &tailTemp);

        shift++;
        t2 = t2->prev;
    }

    remove_leading_zeros(headR, tailR);
}

/* Divide first number by second number */
void division(node **head1, node **tail1,
              node **head2, node **tail2,
              node **headR, node **tailR)
{
    // Check divisor zero
    if (*head2 == NULL)
    {
        printf("ERROR: Division by zero\n");
        exit(FAILURE);
    }
    if ((*head2)->data == 0 && (*head2)->next == NULL)
    {
        printf("ERROR: Division by zero\n");
        exit(FAILURE);
    }

    // Check dividend zero
    if (*head1 == NULL)
    {
        insert_first(headR, tailR, 0);
        return;
    }
    if ((*head1)->data == 0 && (*head1)->next == NULL)
    {
        insert_first(headR, tailR, 0);
        return;
    }

    node *temp_head = NULL, *temp_tail = NULL;
    node *rem_head = NULL, *rem_tail = NULL;
    int count = 0;

    node *t = *head1;
    while (t != NULL)
    {
        insert_last(&temp_head, &temp_tail, t->data);
        t = t->next;
    }

    remove_leading_zeros(&temp_head, &temp_tail);

    while (is_greater(&temp_head, &temp_tail, head2, tail2) != 2)
    {
        subtraction(&temp_head, &temp_tail, head2, tail2, &rem_head, &rem_tail);
        delete_list(&temp_head, &temp_tail);
        temp_head = rem_head; temp_tail = rem_tail;
        rem_head = rem_tail = NULL;
        remove_leading_zeros(&temp_head, &temp_tail);
        count++;
    }

    char buf[20];
    sprintf(buf, "%d", count);
    conv_str_to_list(headR, tailR, buf);
}

/* Print number from linked list */
void print_list(node *head)
{
    while (head != NULL)
    {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}
