#include <stdio.h>

int main()
{
    float num1 = 10.5;
    float num2 = 4.5;
    float sum, average;

    sum = num1 + num2;
    average = sum / 2;

    printf("First number: %.2f\n", num1);
    printf("Second number: %.2f\n", num2);
    printf("Sum: %.2f\n", sum);
    printf("Average: %.2f\n", average);

    return 0;
}

