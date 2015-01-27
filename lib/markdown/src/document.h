/* document.h - generic markdown parser */

#ifndef MARKDOWN_DOCUMENT_H
#define MARKDOWN_DOCUMENT_H

#include "buffer.h"
#include "autolink.h"

#ifdef __cplusplus
extern "C" {
#endif


/*************
 * CONSTANTS *
 *************/

typedef enum markdown_extensions {
	/* block-level extensions */
	MARKDOWN_EXT_TABLES = (1 << 0),
	MARKDOWN_EXT_FENCED_CODE = (1 << 1),
	MARKDOWN_EXT_FOOTNOTES = (1 << 2),

	/* span-level extensions */
	MARKDOWN_EXT_AUTOLINK = (1 << 3),
	MARKDOWN_EXT_STRIKETHROUGH = (1 << 4),
	MARKDOWN_EXT_UNDERLINE = (1 << 5),
	MARKDOWN_EXT_HIGHLIGHT = (1 << 6),
	MARKDOWN_EXT_QUOTE = (1 << 7),
	MARKDOWN_EXT_SUPERSCRIPT = (1 << 8),
	MARKDOWN_EXT_MATH = (1 << 9),

	/* other flags */
	MARKDOWN_EXT_NO_INTRA_EMPHASIS = (1 << 11),
	MARKDOWN_EXT_SPACE_HEADERS = (1 << 12),
	MARKDOWN_EXT_MATH_EXPLICIT = (1 << 13),

	/* negative flags */
	MARKDOWN_EXT_DISABLE_INDENTED_CODE = (1 << 14)
} markdown_extensions;

#define MARKDOWN_EXT_BLOCK (\
	MARKDOWN_EXT_TABLES |\
	MARKDOWN_EXT_FENCED_CODE |\
	MARKDOWN_EXT_FOOTNOTES )

#define MARKDOWN_EXT_SPAN (\
	MARKDOWN_EXT_AUTOLINK |\
	MARKDOWN_EXT_STRIKETHROUGH |\
	MARKDOWN_EXT_UNDERLINE |\
	MARKDOWN_EXT_HIGHLIGHT |\
	MARKDOWN_EXT_QUOTE |\
	MARKDOWN_EXT_SUPERSCRIPT |\
	MARKDOWN_EXT_MATH )

#define MARKDOWN_EXT_FLAGS (\
	MARKDOWN_EXT_NO_INTRA_EMPHASIS |\
	MARKDOWN_EXT_SPACE_HEADERS |\
	MARKDOWN_EXT_MATH_EXPLICIT )

#define MARKDOWN_EXT_NEGATIVE (\
	MARKDOWN_EXT_DISABLE_INDENTED_CODE )

typedef enum markdown_list_flags {
	MARKDOWN_LIST_ORDERED = (1 << 0),
	MARKDOWN_LI_BLOCK = (1 << 1)	/* <li> containing block data */
} markdown_list_flags;

typedef enum markdown_table_flags {
	MARKDOWN_TABLE_ALIGN_LEFT = 1,
	MARKDOWN_TABLE_ALIGN_RIGHT = 2,
	MARKDOWN_TABLE_ALIGN_CENTER = 3,
	MARKDOWN_TABLE_ALIGNMASK = 3,
	MARKDOWN_TABLE_HEADER = 4
} markdown_table_flags;

typedef enum markdown_autolink_type {
	MARKDOWN_AUTOLINK_NONE,		/* used internally when it is not an autolink*/
	MARKDOWN_AUTOLINK_NORMAL,	/* normal http/http/ftp/mailto/etc link */
	MARKDOWN_AUTOLINK_EMAIL		/* e-mail link without explit mailto: */
} markdown_autolink_type;


/*********
 * TYPES *
 *********/

struct markdown_document;
typedef struct markdown_document markdown_document;

struct markdown_renderer_data {
	void *opaque;
};
typedef struct markdown_renderer_data markdown_renderer_data;

/* markdown_renderer - functions for rendering parsed data */
struct markdown_renderer {
	/* state object */
	void *opaque;

	/* block level callbacks - NULL skips the block */
	void (*blockcode)(markdown_buffer *ob, const markdown_buffer *text, const markdown_buffer *lang, const markdown_renderer_data *data);
	void (*blockquote)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*header)(markdown_buffer *ob, const markdown_buffer *content, int level, const markdown_renderer_data *data);
	void (*hrule)(markdown_buffer *ob, const markdown_renderer_data *data);
	void (*list)(markdown_buffer *ob, const markdown_buffer *content, markdown_list_flags flags, const markdown_renderer_data *data);
	void (*listitem)(markdown_buffer *ob, const markdown_buffer *content, markdown_list_flags flags, const markdown_renderer_data *data);
	void (*paragraph)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*table)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*table_header)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*table_body)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*table_row)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*table_cell)(markdown_buffer *ob, const markdown_buffer *content, markdown_table_flags flags, const markdown_renderer_data *data);
	void (*footnotes)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	void (*footnote_def)(markdown_buffer *ob, const markdown_buffer *content, unsigned int num, const markdown_renderer_data *data);
	void (*blockhtml)(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data);

	/* span level callbacks - NULL or return 0 prints the span verbatim */
	int (*autolink)(markdown_buffer *ob, const markdown_buffer *link, markdown_autolink_type type, const markdown_renderer_data *data);
	int (*codespan)(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data);
	int (*double_emphasis)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*emphasis)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*underline)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*highlight)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*quote)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*image)(markdown_buffer *ob, const markdown_buffer *link, const markdown_buffer *title, const markdown_buffer *alt, const markdown_renderer_data *data);
	int (*linebreak)(markdown_buffer *ob, const markdown_renderer_data *data);
	int (*link)(markdown_buffer *ob, const markdown_buffer *content, const markdown_buffer *link, const markdown_buffer *title, const markdown_renderer_data *data);
	int (*triple_emphasis)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*strikethrough)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*superscript)(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data);
	int (*footnote_ref)(markdown_buffer *ob, unsigned int num, const markdown_renderer_data *data);
	int (*math)(markdown_buffer *ob, const markdown_buffer *text, int displaymode, const markdown_renderer_data *data);
	int (*raw_html)(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data);

	/* low level callbacks - NULL copies input directly into the output */
	void (*entity)(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data);
	void (*normal_text)(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data);

	/* miscellaneous callbacks */
	void (*doc_header)(markdown_buffer *ob, int inline_render, const markdown_renderer_data *data);
	void (*doc_footer)(markdown_buffer *ob, int inline_render, const markdown_renderer_data *data);
};
typedef struct markdown_renderer markdown_renderer;


/*************
 * FUNCTIONS *
 *************/

/* markdown_document_new: allocate a new document processor instance */
markdown_document *markdown_document_new(
	const markdown_renderer *renderer,
	markdown_extensions extensions,
	size_t max_nesting
) __attribute__ ((malloc));

/* markdown_document_render: render regular Markdown using the document processor */
void markdown_document_render(markdown_document *doc, markdown_buffer *ob, const uint8_t *data, size_t size);

/* markdown_document_render_inline: render inline Markdown using the document processor */
void markdown_document_render_inline(markdown_document *doc, markdown_buffer *ob, const uint8_t *data, size_t size);

/* markdown_document_free: deallocate a document processor instance */
void markdown_document_free(markdown_document *doc);


#ifdef __cplusplus
}
#endif

#endif /** MARKDOWN_DOCUMENT_H **/
