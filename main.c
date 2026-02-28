#include "apc.h"

int main(int argc, char *argv[])
{
    if (validate_inputs(argv, argc) == FAILURE)   
    {
        printf("Invalid arguments\n");
        return FAILURE;
    }

    node *head1 = NULL, *tail1 = NULL;
    node *head2 = NULL, *tail2 = NULL;
    node *headR = NULL, *tailR = NULL;

    int sign1 = 1, sign2 = 1, result_sign = 1;

    // Handle negative first number
    if (argv[1][0] == '-')
    {
        sign1 = -1;
        argv[1]++;
    }

    // Handle negative second number
    if (argv[3][0] == '-')
    {
        sign2 = -1;
        argv[3]++;
    }

    // Convert operands(string) to linked lists
    conv_str_to_list(&head1, &tail1, argv[1]);
    conv_str_to_list(&head2, &tail2, argv[3]);

    char operator = argv[2][0];

    if (operator == '+')
    {
        if (sign1 == sign2) // Same sign → addition
        {
            addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            result_sign = sign1;
        }
        else // Different signs → subtraction
        {
            subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            int cmp = is_greater(&head1, &tail1, &head2, &tail2);
            if (cmp == 1)
                result_sign = sign1;
            else
                result_sign = sign2;
        }
    }
    else if (operator == '-')
    {
        if (sign1 != sign2) // Different signs → addition
        {
            addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            result_sign = sign1;
        }
        else // Same signs → subtraction
        {
            subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            int cmp = is_greater(&head1, &tail1, &head2, &tail2);
            if (cmp == 0)
                result_sign = 1; // zero positive
            else if (cmp == 1)
                result_sign = sign1;
            else
                result_sign = -sign1;
        }
    }
    else if (operator == 'x')
    {
        multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
        result_sign = sign1 * sign2;
    }
    else if (operator == '/')
    {
        division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
        result_sign = sign1 * sign2;
    }
    else
    {
        printf("Invalid operator\n");
        return FAILURE;
    }

    // Only print minus sign if result is negative and head is not zero
    if (result_sign == -1 && headR != NULL && headR->data != 0)
        printf("-");
            

    print_list(headR);               // Print result

    // Free all memory
    delete_list(&head1, &tail1);
    delete_list(&head2, &tail2);
    delete_list(&headR, &tailR);

    return SUCCESS;
}
