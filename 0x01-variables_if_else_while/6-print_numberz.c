#include <stdio.h>
/**
 * main - print numbers using putchar
* Description: using the main function
* this program prints all single digit numbers of base 10 starting from 0 using putchar
* Return: 0
*/
int main(void)
{
char c;
for (c = '0'; c <= '9'; c++)
{
putchar(c);
}
putchar('\n');
return (0);
}
