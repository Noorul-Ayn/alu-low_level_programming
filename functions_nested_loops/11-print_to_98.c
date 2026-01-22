#include "main.h"
#include <stdio.h>

/**
 * print_to_98 - Prints all natural numbers from n to 98
 * @n: Starting number
 *
 * Description: Prints numbers from n to 98, separated by comma and space
 * If n < 98, counts up; if n > 98, counts down; if n == 98, prints 98
 *
 * Return: void
 */
void print_to_98(int n)
{
	if (n <= 98)
	{
		while (n < 98)
		{
			printf("%d, ", n);
			n++;
		}
		printf("%d\n", n);
	}
	else
	{
		while (n > 98)
		{
			printf("%d, ", n);
			n--;
		}
		printf("%d\n", n);
	}
}
