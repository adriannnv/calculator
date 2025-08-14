
#include "stack.h"

stack_t *
st_create(unsigned int data_size)
{
	stack_t *stack = malloc(sizeof(stack_t));

	stack->list = ll_create(data_size);
	if (!stack) {
		return NULL;
	}

	return stack;
}

unsigned int
st_get_size(stack_t *st)
{
	return ll_get_size(st->list);
}

unsigned int
st_is_empty(stack_t *st)
{
	if (st->list->head)
		return 0;
	else
		return 1;
}

void *
st_peek(stack_t *st)
{
	if (!st) {
		fprintf(stderr, "Error: No stack to be pushed onto\n");
		return NULL;
	}

	return st->list->head->data;
}

void
st_pop(stack_t *st)
{
	if (!st) {
		fprintf(stderr, "Error: No stack to be pushed onto\n");
		return;
	}

	ll_node_t *removed = ll_remove_nth_node(st->list, 0);
	if (removed) {
		free(removed->data);
		free(removed);
	}
}

void
st_push(stack_t *st, void *new_data)
{
	if (!st || !st->list) {
		fprintf(stderr, "Error: No stack to be pushed onto\n");
		return;
	}

	ll_add_nth_node(st->list, 0, new_data);
}

void
st_clear(stack_t *st)
{
	if (!st) {
		fprintf(stderr, "Error: No stack to be cleared");
		return;
	}

    // either while with isempty or this
	int n = ll_get_size(st->list);

	for (int i = 0; i < n; i++) {
		st_pop(st);
	}
}

void
st_free(stack_t *st)
{
	if (!st) {
		fprintf(stderr, "Error: No stack to be freed");
		return;
	}
	st_clear(st);

	free(st->list);
	free(st);
}
