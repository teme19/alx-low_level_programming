#include "lists.h"
/**
 * dlistint_len - returns number of elements in a doubly linked list
 * @h: pointer to a struct of type dlistint_t
 * Return: number of elements
 */
size_t dlistint_len(const dlistint_t *h)
{
	int counter = 0;

	while (h)
	{
		counter++;
		h = h->next;
	}
	return (counter);
}
/**
 * get_dnodeint_at_index - returns the nth node of dlistint_t list
 * @head: pointer to a struct of type dlistint_t
 * @index: index of node to return
 *
 * Return: index of node or NULL if node doesn't exist
 */
dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	unsigned int i;
	size_t len = 0;

	len = dlistint_len(head);
	if (index >= len)
		return (NULL);
	i = 0;
	while (i < index)
	{
		head = head->next;
		i++;
	}
	return (head);
}
