#include "lists.h"
/**
 * sum_dlistint - returns the sum of a doubly linked list
 * @head: pointer to struct of type dlistint_t
 * Return: sum
 */
int sum_dlistint(dlistint_t *head)
{
	int sum = 0;

	if (!head)
		return (0);
	while (head)
	{
		sum += head->n;
		head = head->next;
	}
	return (sum);
}
