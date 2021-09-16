#include "lists.h"

/**
 * delete_dnodeint_at_index - deletes a node at a specified index
 * @head: pointer to pointer to a dlistint_t list
 * @index: index of node to be deleted
 *
 * Return: 1 if it succeeded, -1 if it failed
 */
int delete_dnodeint_at_index(dlistint_t **head, unsigned int index)
{
	unsigned int i;
	size_t len = 0;
	dlistint_t *current = *head, *tmp = NULL;

	if (*head == NULL)
		return (-1);
	len = dlistint_len(*head);
	if (index >= len)
		return (-1);
	if (index == 0 && len > 0)
	{
		tmp = *head;
		*head = (*head)->next;
		if (len != 1)
			(*head)->prev = NULL;
		free(tmp);
		return (1);
	}
	i = 0;
	while (i < index)
	{
		current = current->next;
		i++;
	}
	current->prev->next = current->next;
	if (index != len - 1)
		current->next->prev = current->prev;
	free(current);
	return (1);
}
/**
 * dlistint_len - returns number of elements in a linked list
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
