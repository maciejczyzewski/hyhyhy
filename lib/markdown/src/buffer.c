#include "buffer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void *
markdown_malloc(size_t size)
{
	void *ret = malloc(size);

	if (!ret) {
		fprintf(stderr, "Allocation failed.\n");
		abort();
	}

	return ret;
}

void *
markdown_calloc(size_t nmemb, size_t size)
{
	void *ret = calloc(nmemb, size);

	if (!ret) {
		fprintf(stderr, "Allocation failed.\n");
		abort();
	}

	return ret;
}

void *
markdown_realloc(void *ptr, size_t size)
{
	void *ret = realloc(ptr, size);

	if (!ret) {
		fprintf(stderr, "Allocation failed.\n");
		abort();
	}

	return ret;
}

void
markdown_buffer_init(
	markdown_buffer *buf,
	size_t unit,
	markdown_realloc_callback data_realloc,
	markdown_free_callback data_free,
	markdown_free_callback buffer_free)
{
	assert(buf);

	buf->data = NULL;
	buf->size = buf->asize = 0;
	buf->unit = unit;
	buf->data_realloc = data_realloc;
	buf->data_free = data_free;
	buf->buffer_free = buffer_free;
}

markdown_buffer *
markdown_buffer_new(size_t unit)
{
	markdown_buffer *ret = markdown_malloc(sizeof (markdown_buffer));
	markdown_buffer_init(ret, unit, markdown_realloc, free, free);
	return ret;
}

void
markdown_buffer_free(markdown_buffer *buf)
{
	if (!buf) return;

	buf->data_free(buf->data);

	if (buf->buffer_free)
		buf->buffer_free(buf);
}

void
markdown_buffer_reset(markdown_buffer *buf)
{
	assert(buf && buf->unit);

	buf->data_free(buf->data);
	buf->data = NULL;
	buf->size = buf->asize = 0;
}

void
markdown_buffer_grow(markdown_buffer *buf, size_t neosz)
{
	size_t neoasz;
	assert(buf && buf->unit);

	if (buf->asize >= neosz)
		return;

	neoasz = buf->asize + buf->unit;
	while (neoasz < neosz)
		neoasz += buf->unit;

	buf->data = buf->data_realloc(buf->data, neoasz);
	buf->asize = neoasz;
}

void
markdown_buffer_put(markdown_buffer *buf, const uint8_t *data, size_t size)
{
	assert(buf && buf->unit);

	if (buf->size + size > buf->asize)
		markdown_buffer_grow(buf, buf->size + size);

	memcpy(buf->data + buf->size, data, size);
	buf->size += size;
}

void
markdown_buffer_puts(markdown_buffer *buf, const char *str)
{
	markdown_buffer_put(buf, (const uint8_t *)str, strlen(str));
}

void
markdown_buffer_putc(markdown_buffer *buf, uint8_t c)
{
	assert(buf && buf->unit);

	if (buf->size >= buf->asize)
		markdown_buffer_grow(buf, buf->size + 1);

	buf->data[buf->size] = c;
	buf->size += 1;
}

void
markdown_buffer_set(markdown_buffer *buf, const uint8_t *data, size_t size)
{
	assert(buf && buf->unit);

	if (size > buf->asize)
		markdown_buffer_grow(buf, size);

	memcpy(buf->data, data, size);
	buf->size = size;
}

void
markdown_buffer_sets(markdown_buffer *buf, const char *str)
{
	markdown_buffer_set(buf, (const uint8_t *)str, strlen(str));
}

int
markdown_buffer_eq(const markdown_buffer *buf, const uint8_t *data, size_t size)
{
	if (buf->size != size) return 0;
	return memcmp(buf->data, data, size) == 0;
}

int
markdown_buffer_eqs(const markdown_buffer *buf, const char *str)
{
	return markdown_buffer_eq(buf, (const uint8_t *)str, strlen(str));
}

int
markdown_buffer_prefix(const markdown_buffer *buf, const char *prefix)
{
	size_t i;

	assert(buf && buf->unit);

	for (i = 0; i < buf->size; ++i) {
		if (prefix[i] == 0)
			return 0;

		if (buf->data[i] != prefix[i])
			return buf->data[i] - prefix[i];
	}

	return 0;
}

void
markdown_buffer_slurp(markdown_buffer *buf, size_t size)
{
	assert(buf && buf->unit);

	if (size >= buf->size) {
		buf->size = 0;
		return;
	}

	buf->size -= size;
	memmove(buf->data, buf->data + size, buf->size);
}

const char *
markdown_buffer_cstr(markdown_buffer *buf)
{
	assert(buf && buf->unit);

	if (buf->size < buf->asize && buf->data[buf->size] == 0)
		return (char *)buf->data;

	markdown_buffer_grow(buf, buf->size + 1);
	buf->data[buf->size] = 0;

	return (char *)buf->data;
}

void
markdown_buffer_printf(markdown_buffer *buf, const char *fmt, ...)
{
	va_list ap;
	int n;

	assert(buf && buf->unit);

	if (buf->size >= buf->asize)
		markdown_buffer_grow(buf, buf->size + 1);

	va_start(ap, fmt);
	n = vsnprintf((char *)buf->data + buf->size, buf->asize - buf->size, fmt, ap);
	va_end(ap);

	if (n < 0) {
#ifndef _MSC_VER
		return;
#else
		va_start(ap, fmt);
		n = _vscprintf(fmt, ap);
		va_end(ap);
#endif
	}

	if ((size_t)n >= buf->asize - buf->size) {
		markdown_buffer_grow(buf, buf->size + n + 1);

		va_start(ap, fmt);
		n = vsnprintf((char *)buf->data + buf->size, buf->asize - buf->size, fmt, ap);
		va_end(ap);
	}

	if (n < 0)
		return;

	buf->size += n;
}
