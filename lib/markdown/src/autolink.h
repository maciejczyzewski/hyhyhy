/* autolink.h - versatile autolinker */

#ifndef MARKDOWN_AUTOLINK_H
#define MARKDOWN_AUTOLINK_H

#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

typedef enum markdown_autolink_flags {
	MARKDOWN_AUTOLINK_SHORT_DOMAINS = (1 << 0)
} markdown_autolink_flags;


/*************
 * FUNCTIONS *
 *************/

/* markdown_autolink_is_safe: verify that a URL has a safe protocol */
int markdown_autolink_is_safe(const uint8_t *data, size_t size);

/* markdown_autolink__www: search for the next www link in data */
size_t markdown_autolink__www(size_t *rewind_p, markdown_buffer *link,
	uint8_t *data, size_t offset, size_t size, markdown_autolink_flags flags);

/* markdown_autolink__email: search for the next email in data */
size_t markdown_autolink__email(size_t *rewind_p, markdown_buffer *link,
	uint8_t *data, size_t offset, size_t size, markdown_autolink_flags flags);

/* markdown_autolink__url: search for the next URL in data */
size_t markdown_autolink__url(size_t *rewind_p, markdown_buffer *link,
	uint8_t *data, size_t offset, size_t size, markdown_autolink_flags flags);


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_AUTOLINK_H **/
