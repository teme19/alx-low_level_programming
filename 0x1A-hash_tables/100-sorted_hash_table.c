#include "hash_tables.h"
/**
 * shash_table_create - creates a sorted hash table
 * @size: size of sorted hash table
 *
 * Return: pointer to a struct of type shash_table_t
 */
shash_table_t *shash_table_create(unsigned long int size)
{
	shash_table_t *ht = NULL;

	if (size == 0)
		return (NULL);
	ht = calloc(1, sizeof(shash_table_t));
	if (ht == NULL)
	{
		free(ht);
		return (NULL);
	}
	ht->array = calloc(size, sizeof(shash_node_t *));
	if (ht->array == NULL)
	{
		free(ht->array);
		return (NULL);
	}
	ht->size = size;
	return (ht);
}
/**
 * shash_table_set - adds an element to the sorted hash table
 * @ht: pointer to a struct of type shash_table_t
 * @key: key to insert
 * @value: associated value to insert
 *
 * Return: 1 if it succeeded, 0 otherwise
 */
int shash_table_set(shash_table_t *ht, const char *key, const char *value)
{
	shash_node_t *bucket = NULL, *tmp = NULL;
	unsigned long int hash = 0;

	if (!ht || !key || !*key || !value || !*value)
		return (0);
	hash = key_index((unsigned char *)key, ht->size);
	tmp = ht->array[hash];
	while (tmp != NULL)
	{
		if (strcmp(tmp->key, (char *)key) == 0)
		{
			free(tmp->value);
			tmp->value = strdup((char *)value);
			if (!tmp->value)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	bucket = malloc(sizeof(shash_node_t));
	if (!bucket)
		return (0);
	bucket->key = strdup((char *)key);
	if (bucket->key == NULL)
	{
		free(bucket);
		return (0);
	}
	bucket->value = strdup(value);
	if (bucket->value == NULL)
	{
		free(bucket->key);
		free(bucket);
		return (0);
	}
	bucket->next = ht->array[hash];
	ht->array[hash] = bucket;
	sorted_insert(ht, bucket);
	return (1);
}
/**
 * sorted_insert - adds an element to doubly linked list
 * @ht: pointer to a pointer to a struct of type shash_table_t
 * @bucket: node to insert
 *
 * Return: 1 if it succeeded, 0 otherwise
 */
int sorted_insert(shash_table_t *ht,  shash_node_t *bucket)
{
	shash_node_t *current = NULL;

	if (ht->shead == NULL)
	{
		ht->shead = bucket;
		ht->stail = bucket;
		bucket->snext = NULL;
		bucket->sprev = NULL;
		return (1);
	}
	current = ht->shead;
	while (current != NULL)
	{
		if (strcmp(bucket->key, current->key) < 0)
		{

			if (current->sprev == NULL)
			{
				current->sprev = bucket;
				bucket->sprev = NULL;
				bucket->snext = current;
				ht->shead = bucket;
				return (1);
			}
			bucket->sprev = current->sprev;
			bucket->snext = current;
			current->sprev->snext = bucket;
			current->sprev = bucket;
			return (1);
		}
		if (current->snext == NULL)
			break;
		current = current->snext;
	}
	bucket->snext = NULL;
	bucket->sprev = current;
	current->snext = bucket;
	ht->stail = bucket;
	return (1);
}
/**
 * shash_table_get -retrieves a value associated with a key
 * @ht: pointer to a hash table data structure
 * @key: pointer to a key to retrieve
 *
 * Return: value associated with element or NULL if key couldn't be found
 */
char *shash_table_get(const shash_table_t *ht, const char *key)
{
	shash_node_t *tmp = NULL;
	unsigned long int hash = 0;

	if (!key || !*key || !ht)
		return (NULL);
	hash = key_index((unsigned char *)key, ht->size);
	tmp = ht->array[hash];
	while (tmp != NULL)
	{
		if (strcmp(tmp->key, (char *)key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
/**
 * shash_table_print - prints a hash table using sorted list
 * @ht: a pointer to the hash table
 *
 * Return: void
 */
void shash_table_print(const shash_table_t *ht)
{
	int flag = 0;
	shash_node_t *current = NULL;

	if (!ht || !ht->shead)
		return;
	printf("{");
	current = ht->shead;
	while (current != NULL)
	{
		if (flag == 0)
		{
			printf("'%s': '%s'", current->key, current->value);
			flag = 1;
		}
		else
			printf(", '%s': '%s'", current->key, current->value);
		current = current->snext;
		}
	printf("}\n");
}
/**
 * shash_table_print_rev - prints a hash table using sorted list
 * @ht: a pointer to the hash table
 *
 * Return: void
 */
void shash_table_print_rev(const shash_table_t *ht)
{
	int flag = 0;
	shash_node_t *current = NULL;

	if (!ht || !ht->stail)
		return;
	printf("{");
	current = ht->stail;
	while (current != NULL)
	{
		if (flag == 0)
		{
			printf("'%s': '%s'", current->key, current->value);
			flag = 1;
		}
		else
			printf(", '%s': '%s'", current->key, current->value);
		current = current->sprev;
		}
	printf("}\n");
}
/**
 * shash_table_delete - deletes a hash table
 *
 * @ht: pointer to hash table data structure
 * Return: void
 */
void shash_table_delete(shash_table_t *ht)
{
	unsigned int i = 0;
	shash_node_t *head = NULL;
	shash_node_t *tmp = NULL;

	if (!ht)
		return;
	for (i = 0; i < ht->size; i++)
	{
		head = ht->array[i];
		while (head != NULL)
		{
			tmp = head->next;
			free(head->key);
			free(head->value);
			free(head);
			head = tmp;
		}
	}
	free(ht->array);
	free(ht);
}
