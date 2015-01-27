/* buffer.h - simple, fast buffers */

#ifndef MARKDOWN_BUFFER_H
#define MARKDOWN_BUFFER_H

#include <stdio.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_MSC_VER)
#define __attribute__(x)
#define inline __inline
#define __builtin_expect(x,n) x
#endif


/*********
 * TYPES *
 *********/

typedef void *(*markdown_realloc_callback)(void *, size_t);
typedef void (*markdown_free_callback)(void *);

struct markdown_buffer {
	uint8_t *data;	/* actual character data */
	size_t size;	/* size of the string */
	size_t asize;	/* allocated size (0 = volatile buffer) */
	size_t unit;	/* reallocation unit size (0 = read-only buffer) */

	markdown_realloc_callback data_realloc;
	markdown_free_callback data_free;
	markdown_free_callback buffer_free;
};

typedef struct markdown_buffer markdown_buffer;


/*************
 * FUNCTIONS *
 *************/

/* allocation wrappers */
void *markdown_malloc(size_t size) __attribute__ ((malloc));
void *markdown_calloc(size_t nmemb, size_t size) __attribute__ ((malloc));
void *markdown_realloc(void *ptr, size_t size) __attribute__ ((malloc));

/* markdown_buffer_init: initialize a buffer with custom allocators */
void markdown_buffer_init(
	markdown_buffer *buffer,
	size_t unit,
	markdown_realloc_callback data_realloc,
	markdown_free_callback data_free,
	markdown_free_callback buffer_free
);

/* markdown_buffer_new: allocate a new buffer */
markdown_buffer *markdown_buffer_new(size_t unit) __attribute__ ((malloc));

/* markdown_buffer_reset: free internal data of the buffer */
void markdown_buffer_reset(markdown_buffer *buf);

/* markdown_buffer_grow: increase the allocated size to the given value */
void markdown_buffer_grow(markdown_buffer *buf, size_t neosz);

/* markdown_buffer_put: append raw data to a buffer */
void markdown_buffer_put(markdown_buffer *buf, const uint8_t *data, size_t size);

/* markdown_buffer_puts: append a NUL-terminated string to a buffer */
void markdown_buffer_puts(markdown_buffer *buf, const char *str);

/* markdown_buffer_putc: append a single char to a buffer */
void markdown_buffer_putc(markdown_buffer *buf, uint8_t c);

/* markdown_buffer_set: replace the buffer's contents with raw data */
void markdown_buffer_set(markdown_buffer *buf, const uint8_t *data, size_t size);

/* markdown_buffer_sets: replace the buffer's contents with a NUL-terminated string */
void markdown_buffer_sets(markdown_buffer *buf, const char *str);

/* markdown_buffer_eq: compare a buffer's data with other data for equality */
int markdown_buffer_eq(const markdown_buffer *buf, const uint8_t *data, size_t size);

/* markdown_buffer_eq: compare a buffer's data with NUL-terminated string for equality */
int markdown_buffer_eqs(const markdown_buffer *buf, const char *str);

/* markdown_buffer_prefix: compare the beginning of a buffer with a string */
int markdown_buffer_prefix(const markdown_buffer *buf, const char *prefix);

/* markdown_buffer_slurp: remove a given number of bytes from the head of the buffer */
void markdown_buffer_slurp(markdown_buffer *buf, size_t size);

/* markdown_buffer_cstr: NUL-termination of the string array (making a C-string) */
const char *markdown_buffer_cstr(markdown_buffer *buf);

/* markdown_buffer_printf: formatted printing to a buffer */
void markdown_buffer_printf(markdown_buffer *buf, const char *fmt, ...) __attribute__ ((format (printf, 2, 3)));

/* markdown_buffer_free: free the buffer */
void markdown_buffer_free(markdown_buffer *buf);


/* MARKDOWN_BUFPUTSL: optimized markdown_buffer_puts of a string literal */
#define MARKDOWN_BUFPUTSL(output, literal) \
	markdown_buffer_put(output, (const uint8_t *)literal, sizeof(literal) - 1)

/* MARKDOWN_BUFSETSL: optimized markdown_buffer_sets of a string literal */
#define MARKDOWN_BUFSETSL(output, literal) \
	markdown_buffer_set(output, (const uint8_t *)literal, sizeof(literal) - 1)

/* MARKDOWN_BUFEQSL: optimized markdown_buffer_eqs of a string literal */
#define MARKDOWN_BUFEQSL(output, literal) \
	markdown_buffer_eq(output, (const uint8_t *)literal, sizeof(literal) - 1)


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_BUFFER_H **/
