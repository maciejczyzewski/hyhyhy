/* stack.h - simple stacking */

#ifndef MARKDOWN_STACK_H
#define MARKDOWN_STACK_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif


/*********
 * TYPES *
 *********/

struct markdown_stack {
	void **item;
	size_t size;
	size_t asize;
};
typedef struct markdown_stack markdown_stack;


/*************
 * FUNCTIONS *
 *************/

/* markdown_stack_init: initialize a stack */
void markdown_stack_init(markdown_stack *st, size_t initial_size);

/* markdown_stack_uninit: free internal data of the stack */
void markdown_stack_uninit(markdown_stack *st);

/* markdown_stack_grow: increase the allocated size to the given value */
void markdown_stack_grow(markdown_stack *st, size_t neosz);

/* markdown_stack_push: push an item to the top of the stack */
void markdown_stack_push(markdown_stack *st, void *item);

/* markdown_stack_pop: retrieve and remove the item at the top of the stack */
void *markdown_stack_pop(markdown_stack *st);

/* markdown_stack_top: retrieve the item at the top of the stack */
void *markdown_stack_top(const markdown_stack *st);


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_STACK_H **/
