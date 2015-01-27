/* html.h - HTML renderer and utilities */

#ifndef MARKDOWN_HTML_H
#define MARKDOWN_HTML_H

#include "document.h"
#include "buffer.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

typedef enum markdown_html_flags {
	MARKDOWN_HTML_SKIP_HTML = (1 << 0),
	MARKDOWN_HTML_ESCAPE = (1 << 1),
	MARKDOWN_HTML_HARD_WRAP = (1 << 2),
	MARKDOWN_HTML_USE_XHTML = (1 << 3)
} markdown_html_flags;

typedef enum markdown_html_tag {
	MARKDOWN_HTML_TAG_NONE = 0,
	MARKDOWN_HTML_TAG_OPEN,
	MARKDOWN_HTML_TAG_CLOSE
} markdown_html_tag;


/*********
 * TYPES *
 *********/

struct markdown_html_renderer_state {
	void *opaque;

	struct {
		int header_count;
		int current_level;
		int level_offset;
		int nesting_level;
	} toc_data;

	markdown_html_flags flags;

	/* extra callbacks */
	void (*link_attributes)(markdown_buffer *ob, const markdown_buffer *url, const markdown_renderer_data *data);
};
typedef struct markdown_html_renderer_state markdown_html_renderer_state;


/*************
 * FUNCTIONS *
 *************/

/* markdown_html_smartypants: process an HTML snippet using SmartyPants for smart punctuation */
void markdown_html_smartypants(markdown_buffer *ob, const uint8_t *data, size_t size);

/* markdown_html_is_tag: checks if data starts with a specific tag, returns the tag type or NONE */
markdown_html_tag markdown_html_is_tag(const uint8_t *data, size_t size, const char *tagname);


/* markdown_html_renderer_new: allocates a regular HTML renderer */
markdown_renderer *markdown_html_renderer_new(
	markdown_html_flags render_flags,
	int nesting_level
) __attribute__ ((malloc));

/* markdown_html_toc_renderer_new: like markdown_html_renderer_new, but the returned renderer produces the Table of Contents */
markdown_renderer *markdown_html_toc_renderer_new(
	int nesting_level
) __attribute__ ((malloc));

/* markdown_html_renderer_free: deallocate an HTML renderer */
void markdown_html_renderer_free(markdown_renderer *renderer);


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_HTML_H **/
