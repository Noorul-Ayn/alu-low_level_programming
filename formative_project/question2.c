#include <stdio.h>

int main(void)
{
    int choice;
    float num1, num2, result;

    while (1)   /* infinite loop until user exits */
    {
        printf("\n===== SIMPLE CALCULATOR MENU =====\n");
        printf("1. Add two numbers\n");
        printf("2. Subtract two numbers\n");
        printf("3. Multiply two numbers\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 4)
        {
            printf("Exiting program...\n");
            break;   /* exits the loop */
        }

        if (choice < 1 || choice > 4)
        {
            printf("Invalid choice. Please try again.\n");
            continue;   /* skips to next loop iteration */
        }

        printf("Enter first number: ");
        scanf("%f", &num1);

        printf("Enter second number: ");
        scanf("%f", &num2);

        switch (choice)
        {
            case 1:
                result = num1 + num2;
                printf("Result: %.2f\n", result);
                break;

            case 2:
                result = num1 - num2;
                printf("Result: %.2f\n", result);
                break;

            case 3:
                result = num1 * num2;
                printf("Result: %.2f\n", result);
                break;
        }
    }

    return 0;
}

