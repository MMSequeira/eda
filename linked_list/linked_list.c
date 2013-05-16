#include <stdio.h>
#include <stdlib.h>

struct singly_linked_int_node {
	int value;
	struct singly_linked_int_node *next;
};

int main()
{
	struct singly_linked_int_node *first;

	first = malloc(sizeof(struct singly_linked_int_node));
	//(*first).value = 10;
	first->value = 10;
	first->next = NULL;

	first->next = malloc(sizeof(struct singly_linked_int_node));
	first->next->value = 20;
	first->next->next = NULL;

	struct singly_linked_int_node *new_node =
		malloc(sizeof(struct singly_linked_int_node));
	new_node->value = 0;
	new_node->next = first;
	first = new_node;

	for (struct singly_linked_int_node *node_pointer = first;
		node_pointer != NULL;
		node_pointer = node_pointer->next)
		printf("%d\n", node_pointer->value);

	printf("Hello world!\n");

	return EXIT_SUCCESS;
}
