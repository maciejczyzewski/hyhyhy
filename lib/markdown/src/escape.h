/* escape.h - escape utilities */

#ifndef MARKDOWN_ESCAPE_H
#define MARKDOWN_ESCAPE_H

#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * FUNCTIONS *
 *************/

/* markdown_escape_href: escape (part of) a URL inside HTML */
void markdown_escape_href(markdown_buffer *ob, const uint8_t *data, size_t size);

/* markdown_escape_html: escape HTML */
void markdown_escape_html(markdown_buffer *ob, const uint8_t *data, size_t size, int secure);


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_ESCAPE_H **/
