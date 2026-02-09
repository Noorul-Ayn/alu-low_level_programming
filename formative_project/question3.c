#include <stdio.h>

/* Recursive function to calculate factorial */
long factorial(int n)
{
    if (n <= 1)
        return 1;          // base case
    else
        return n * factorial(n - 1); // recursive case
}

/* Function to display result for a number */
void displayFactorial(int n)
{
    long result = factorial(n);  // reuse recursive function
    printf("Factorial of %d is %ld\n", n, result);
}

int main(void)
{
    int num1, num2;

    /* Example 1 */
    num1 = 5;
    displayFactorial(num1);

    /* Example 2 */
    num2 = 7;
    displayFactorial(num2);

    return 0;
}

