#include "stack.h"

#include "buffer.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

void
markdown_stack_init(markdown_stack *st, size_t initial_size)
{
	assert(st);

	st->item = NULL;
	st->size = st->asize = 0;

	if (!initial_size)
		initial_size = 8;

	markdown_stack_grow(st, initial_size);
}

void
markdown_stack_uninit(markdown_stack *st)
{
	assert(st);

	free(st->item);
}

void
markdown_stack_grow(markdown_stack *st, size_t neosz)
{
	assert(st);

	if (st->asize >= neosz)
		return;

	st->item = markdown_realloc(st->item, neosz * sizeof(void *));
	memset(st->item + st->asize, 0x0, (neosz - st->asize) * sizeof(void *));

	st->asize = neosz;

	if (st->size > neosz)
		st->size = neosz;
}

void
markdown_stack_push(markdown_stack *st, void *item)
{
	assert(st);

	if (st->size >= st->asize)
		markdown_stack_grow(st, st->size * 2);

	st->item[st->size++] = item;
}

void *
markdown_stack_pop(markdown_stack *st)
{
	assert(st);

	if (!st->size)
		return NULL;

	return st->item[--st->size];
}

void *
markdown_stack_top(const markdown_stack *st)
{
	assert(st);

	if (!st->size)
		return NULL;

	return st->item[st->size - 1];
}
