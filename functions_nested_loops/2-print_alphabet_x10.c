#include "main.h"

/**
 * print_alphabet_x10 - Prints the alphabet 10 times in lowercase
 *
 * Description: Uses nested loops to print a-z ten times, each on a new line
 *
 * Return: void
 */
void print_alphabet_x10(void)
{
	int count;
	char letter;

	for (count = 0; count < 10; count++)
	{
		for (letter = 'a'; letter <= 'z'; letter++)
		{
			_putchar(letter);
		}
		_putchar('\n');
	}
}
