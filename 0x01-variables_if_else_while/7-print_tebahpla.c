#include <stdio.h>
/**
* main - print alphabet
* Description: using the main function
* this program prints the lowercase alphabet in reverse
* Return: 0
*/
int main(void)
{
char c;
for (c = 'z'; c >= 'a'; c--)
{
putchar(c);
}
putchar('\n');
return (0);
}
