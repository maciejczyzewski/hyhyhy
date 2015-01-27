#include "html.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "escape.h"

#define USE_XHTML(opt) (opt->flags & MARKDOWN_HTML_USE_XHTML)

markdown_html_tag
markdown_html_is_tag(const uint8_t *data, size_t size, const char *tagname)
{
	size_t i;
	int closed = 0;

	if (size < 3 || data[0] != '<')
		return MARKDOWN_HTML_TAG_NONE;

	i = 1;

	if (data[i] == '/') {
		closed = 1;
		i++;
	}

	for (; i < size; ++i, ++tagname) {
		if (*tagname == 0)
			break;

		if (data[i] != *tagname)
			return MARKDOWN_HTML_TAG_NONE;
	}

	if (i == size)
		return MARKDOWN_HTML_TAG_NONE;

	if (isspace(data[i]) || data[i] == '>')
		return closed ? MARKDOWN_HTML_TAG_CLOSE : MARKDOWN_HTML_TAG_OPEN;

	return MARKDOWN_HTML_TAG_NONE;
}

static void escape_html(markdown_buffer *ob, const uint8_t *source, size_t length)
{
	markdown_escape_html(ob, source, length, 0);
}

static void escape_href(markdown_buffer *ob, const uint8_t *source, size_t length)
{
	markdown_escape_href(ob, source, length);
}

/********************
 * GENERIC RENDERER *
 ********************/
static int
rndr_autolink(markdown_buffer *ob, const markdown_buffer *link, markdown_autolink_type type, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;

	if (!link || !link->size)
		return 0;

	MARKDOWN_BUFPUTSL(ob, "<a href=\"");
	if (type == MARKDOWN_AUTOLINK_EMAIL)
		MARKDOWN_BUFPUTSL(ob, "mailto:");
	escape_href(ob, link->data, link->size);

	if (state->link_attributes) {
		markdown_buffer_putc(ob, '\"');
		state->link_attributes(ob, link, data);
		markdown_buffer_putc(ob, '>');
	} else {
		MARKDOWN_BUFPUTSL(ob, "\">");
	}

	/*
	 * Pretty printing: if we get an email address as
	 * an actual URI, e.g. `mailto:foo@bar.com`, we don't
	 * want to print the `mailto:` prefix
	 */
	if (markdown_buffer_prefix(link, "mailto:") == 0) {
		escape_html(ob, link->data + 7, link->size - 7);
	} else {
		escape_html(ob, link->data, link->size);
	}

	MARKDOWN_BUFPUTSL(ob, "</a>");

	return 1;
}

static void
rndr_blockcode(markdown_buffer *ob, const markdown_buffer *text, const markdown_buffer *lang, const markdown_renderer_data *data)
{
	if (ob->size) markdown_buffer_putc(ob, '\n');

	if (lang) {
		MARKDOWN_BUFPUTSL(ob, "<pre><code class=\"language-");
		escape_html(ob, lang->data, lang->size);
		MARKDOWN_BUFPUTSL(ob, "\">");
	} else {
		MARKDOWN_BUFPUTSL(ob, "<pre><code>");
	}

	if (text)
		escape_html(ob, text->data, text->size);

	MARKDOWN_BUFPUTSL(ob, "</code></pre>\n");
}

static void
rndr_blockquote(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (ob->size) markdown_buffer_putc(ob, '\n');
	MARKDOWN_BUFPUTSL(ob, "<blockquote>\n");
	if (content) markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</blockquote>\n");
}

static int
rndr_codespan(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data)
{
	MARKDOWN_BUFPUTSL(ob, "<code>");
	if (text) escape_html(ob, text->data, text->size);
	MARKDOWN_BUFPUTSL(ob, "</code>");
	return 1;
}

static int
rndr_strikethrough(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size)
		return 0;

	MARKDOWN_BUFPUTSL(ob, "<del>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</del>");
	return 1;
}

static int
rndr_double_emphasis(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size)
		return 0;

	MARKDOWN_BUFPUTSL(ob, "<strong>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</strong>");

	return 1;
}

static int
rndr_emphasis(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size) return 0;
	MARKDOWN_BUFPUTSL(ob, "<em>");
	if (content) markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</em>");
	return 1;
}

static int
rndr_underline(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size)
		return 0;

	MARKDOWN_BUFPUTSL(ob, "<u>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</u>");

	return 1;
}

static int
rndr_highlight(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size)
		return 0;

	MARKDOWN_BUFPUTSL(ob, "<mark>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</mark>");

	return 1;
}

static int
rndr_quote(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size)
		return 0;

	MARKDOWN_BUFPUTSL(ob, "<q>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</q>");

	return 1;
}

static int
rndr_linebreak(markdown_buffer *ob, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;
	markdown_buffer_puts(ob, USE_XHTML(state) ? "<br/>\n" : "<br>\n");
	return 1;
}

static void
rndr_header(markdown_buffer *ob, const markdown_buffer *content, int level, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;

	if (ob->size)
		markdown_buffer_putc(ob, '\n');

	if (level <= state->toc_data.nesting_level)
		markdown_buffer_printf(ob, "<h%d id=\"toc_%d\">", level, state->toc_data.header_count++);
	else
		markdown_buffer_printf(ob, "<h%d>", level);

	if (content) markdown_buffer_put(ob, content->data, content->size);
	markdown_buffer_printf(ob, "</h%d>\n", level);
}

static int
rndr_link(markdown_buffer *ob, const markdown_buffer *content, const markdown_buffer *link, const markdown_buffer *title, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;

	MARKDOWN_BUFPUTSL(ob, "<a href=\"");

	if (link && link->size)
		escape_href(ob, link->data, link->size);

	if (title && title->size) {
		MARKDOWN_BUFPUTSL(ob, "\" title=\"");
		escape_html(ob, title->data, title->size);
	}

	if (state->link_attributes) {
		markdown_buffer_putc(ob, '\"');
		state->link_attributes(ob, link, data);
		markdown_buffer_putc(ob, '>');
	} else {
		MARKDOWN_BUFPUTSL(ob, "\">");
	}

	if (content && content->size) markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</a>");
	return 1;
}

static void
rndr_list(markdown_buffer *ob, const markdown_buffer *content, markdown_list_flags flags, const markdown_renderer_data *data)
{
	if (ob->size) markdown_buffer_putc(ob, '\n');
	markdown_buffer_put(ob, (const uint8_t *)(flags & MARKDOWN_LIST_ORDERED ? "<ol>\n" : "<ul>\n"), 5);
	if (content) markdown_buffer_put(ob, content->data, content->size);
	markdown_buffer_put(ob, (const uint8_t *)(flags & MARKDOWN_LIST_ORDERED ? "</ol>\n" : "</ul>\n"), 6);
}

static void
rndr_listitem(markdown_buffer *ob, const markdown_buffer *content, markdown_list_flags flags, const markdown_renderer_data *data)
{
	MARKDOWN_BUFPUTSL(ob, "<li>");
	if (content) {
		size_t size = content->size;
		while (size && content->data[size - 1] == '\n')
			size--;

		markdown_buffer_put(ob, content->data, size);
	}
	MARKDOWN_BUFPUTSL(ob, "</li>\n");
}

static void
rndr_paragraph(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;
	size_t i = 0;

	if (ob->size) markdown_buffer_putc(ob, '\n');

	if (!content || !content->size)
		return;

	while (i < content->size && isspace(content->data[i])) i++;

	if (i == content->size)
		return;

	MARKDOWN_BUFPUTSL(ob, "<p>");
	if (state->flags & MARKDOWN_HTML_HARD_WRAP) {
		size_t org;
		while (i < content->size) {
			org = i;
			while (i < content->size && content->data[i] != '\n')
				i++;

			if (i > org)
				markdown_buffer_put(ob, content->data + org, i - org);

			/*
			 * do not insert a line break if this newline
			 * is the last character on the paragraph
			 */
			if (i >= content->size - 1)
				break;

			rndr_linebreak(ob, data);
			i++;
		}
	} else {
		markdown_buffer_put(ob, content->data + i, content->size - i);
	}
	MARKDOWN_BUFPUTSL(ob, "</p>\n");
}

static void
rndr_raw_block(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data)
{
	size_t org, sz;

	if (!text)
		return;

	/* FIXME: Do we *really* need to trim the HTML? How does that make a difference? */
	sz = text->size;
	while (sz > 0 && text->data[sz - 1] == '\n')
		sz--;

	org = 0;
	while (org < sz && text->data[org] == '\n')
		org++;

	if (org >= sz)
		return;

	if (ob->size)
		markdown_buffer_putc(ob, '\n');

	markdown_buffer_put(ob, text->data + org, sz - org);
	markdown_buffer_putc(ob, '\n');
}

static int
rndr_triple_emphasis(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size) return 0;
	MARKDOWN_BUFPUTSL(ob, "<strong><em>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</em></strong>");
	return 1;
}

static void
rndr_hrule(markdown_buffer *ob, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;
	if (ob->size) markdown_buffer_putc(ob, '\n');
	markdown_buffer_puts(ob, USE_XHTML(state) ? "<hr/>\n" : "<hr>\n");
}

static int
rndr_image(markdown_buffer *ob, const markdown_buffer *link, const markdown_buffer *title, const markdown_buffer *alt, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;
	if (!link || !link->size) return 0;

	MARKDOWN_BUFPUTSL(ob, "<img src=\"");
	escape_href(ob, link->data, link->size);
	MARKDOWN_BUFPUTSL(ob, "\" alt=\"");

	if (alt && alt->size)
		escape_html(ob, alt->data, alt->size);

	if (title && title->size) {
		MARKDOWN_BUFPUTSL(ob, "\" title=\"");
		escape_html(ob, title->data, title->size); }

	markdown_buffer_puts(ob, USE_XHTML(state) ? "\"/>" : "\">");
	return 1;
}

static int
rndr_raw_html(markdown_buffer *ob, const markdown_buffer *text, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;

	/* ESCAPE overrides SKIP_HTML. It doesn't look to see if
	 * there are any valid tags, just escapes all of them. */
	if((state->flags & MARKDOWN_HTML_ESCAPE) != 0) {
		escape_html(ob, text->data, text->size);
		return 1;
	}

	if ((state->flags & MARKDOWN_HTML_SKIP_HTML) != 0)
		return 1;

	markdown_buffer_put(ob, text->data, text->size);
	return 1;
}

static void
rndr_table(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
    if (ob->size) markdown_buffer_putc(ob, '\n');
    MARKDOWN_BUFPUTSL(ob, "<table>\n");
    markdown_buffer_put(ob, content->data, content->size);
    MARKDOWN_BUFPUTSL(ob, "</table>\n");
}

static void
rndr_table_header(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
    if (ob->size) markdown_buffer_putc(ob, '\n');
    MARKDOWN_BUFPUTSL(ob, "<thead>\n");
    markdown_buffer_put(ob, content->data, content->size);
    MARKDOWN_BUFPUTSL(ob, "</thead>\n");
}

static void
rndr_table_body(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
    if (ob->size) markdown_buffer_putc(ob, '\n');
    MARKDOWN_BUFPUTSL(ob, "<tbody>\n");
    markdown_buffer_put(ob, content->data, content->size);
    MARKDOWN_BUFPUTSL(ob, "</tbody>\n");
}

static void
rndr_tablerow(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	MARKDOWN_BUFPUTSL(ob, "<tr>\n");
	if (content) markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</tr>\n");
}

static void
rndr_tablecell(markdown_buffer *ob, const markdown_buffer *content, markdown_table_flags flags, const markdown_renderer_data *data)
{
	if (flags & MARKDOWN_TABLE_HEADER) {
		MARKDOWN_BUFPUTSL(ob, "<th");
	} else {
		MARKDOWN_BUFPUTSL(ob, "<td");
	}

	switch (flags & MARKDOWN_TABLE_ALIGNMASK) {
	case MARKDOWN_TABLE_ALIGN_CENTER:
		MARKDOWN_BUFPUTSL(ob, " style=\"text-align: center\">");
		break;

	case MARKDOWN_TABLE_ALIGN_LEFT:
		MARKDOWN_BUFPUTSL(ob, " style=\"text-align: left\">");
		break;

	case MARKDOWN_TABLE_ALIGN_RIGHT:
		MARKDOWN_BUFPUTSL(ob, " style=\"text-align: right\">");
		break;

	default:
		MARKDOWN_BUFPUTSL(ob, ">");
	}

	if (content)
		markdown_buffer_put(ob, content->data, content->size);

	if (flags & MARKDOWN_TABLE_HEADER) {
		MARKDOWN_BUFPUTSL(ob, "</th>\n");
	} else {
		MARKDOWN_BUFPUTSL(ob, "</td>\n");
	}
}

static int
rndr_superscript(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (!content || !content->size) return 0;
	MARKDOWN_BUFPUTSL(ob, "<sup>");
	markdown_buffer_put(ob, content->data, content->size);
	MARKDOWN_BUFPUTSL(ob, "</sup>");
	return 1;
}

static void
rndr_normal_text(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	if (content)
		escape_html(ob, content->data, content->size);
}

static void
rndr_footnotes(markdown_buffer *ob, const markdown_buffer *content, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;

	if (ob->size) markdown_buffer_putc(ob, '\n');
	MARKDOWN_BUFPUTSL(ob, "<div class=\"footnotes\">\n");
	markdown_buffer_puts(ob, USE_XHTML(state) ? "<hr/>\n" : "<hr>\n");
	MARKDOWN_BUFPUTSL(ob, "<ol>\n");

	if (content) markdown_buffer_put(ob, content->data, content->size);

	MARKDOWN_BUFPUTSL(ob, "\n</ol>\n</div>\n");
}

static void
rndr_footnote_def(markdown_buffer *ob, const markdown_buffer *content, unsigned int num, const markdown_renderer_data *data)
{
	size_t i = 0;
	int pfound = 0;

	/* insert anchor at the end of first paragraph block */
	if (content) {
		while ((i+3) < content->size) {
			if (content->data[i++] != '<') continue;
			if (content->data[i++] != '/') continue;
			if (content->data[i++] != 'p' && content->data[i] != 'P') continue;
			if (content->data[i] != '>') continue;
			i -= 3;
			pfound = 1;
			break;
		}
	}

	markdown_buffer_printf(ob, "\n<li id=\"fn%d\">\n", num);
	if (pfound) {
		markdown_buffer_put(ob, content->data, i);
		markdown_buffer_printf(ob, "&nbsp;<a href=\"#fnref%d\" rev=\"footnote\">&#8617;</a>", num);
		markdown_buffer_put(ob, content->data + i, content->size - i);
	} else if (content) {
		markdown_buffer_put(ob, content->data, content->size);
	}
	MARKDOWN_BUFPUTSL(ob, "</li>\n");
}

static int
rndr_footnote_ref(markdown_buffer *ob, unsigned int num, const markdown_renderer_data *data)
{
	markdown_buffer_printf(ob, "<sup id=\"fnref%d\"><a href=\"#fn%d\" rel=\"footnote\">%d</a></sup>", num, num, num);
	return 1;
}

static int
rndr_math(markdown_buffer *ob, const markdown_buffer *text, int displaymode, const markdown_renderer_data *data)
{
	markdown_buffer_put(ob, (const uint8_t *)(displaymode ? "\\[" : "\\("), 2);
	escape_html(ob, text->data, text->size);
	markdown_buffer_put(ob, (const uint8_t *)(displaymode ? "\\]" : "\\)"), 2);
	return 1;
}

static void
toc_header(markdown_buffer *ob, const markdown_buffer *content, int level, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state = data->opaque;

	if (level <= state->toc_data.nesting_level) {
		/* set the level offset if this is the first header
		 * we're parsing for the document */
		if (state->toc_data.current_level == 0)
			state->toc_data.level_offset = level - 1;

		level -= state->toc_data.level_offset;

		if (level > state->toc_data.current_level) {
			while (level > state->toc_data.current_level) {
				MARKDOWN_BUFPUTSL(ob, "<ul>\n<li>\n");
				state->toc_data.current_level++;
			}
		} else if (level < state->toc_data.current_level) {
			MARKDOWN_BUFPUTSL(ob, "</li>\n");
			while (level < state->toc_data.current_level) {
				MARKDOWN_BUFPUTSL(ob, "</ul>\n</li>\n");
				state->toc_data.current_level--;
			}
			MARKDOWN_BUFPUTSL(ob,"<li>\n");
		} else {
			MARKDOWN_BUFPUTSL(ob,"</li>\n<li>\n");
		}

		markdown_buffer_printf(ob, "<a href=\"#toc_%d\">", state->toc_data.header_count++);
		if (content) markdown_buffer_put(ob, content->data, content->size);
		MARKDOWN_BUFPUTSL(ob, "</a>\n");
	}
}

static int
toc_link(markdown_buffer *ob, const markdown_buffer *content, const markdown_buffer *link, const markdown_buffer *title, const markdown_renderer_data *data)
{
	if (content && content->size) markdown_buffer_put(ob, content->data, content->size);
	return 1;
}

static void
toc_finalize(markdown_buffer *ob, int inline_render, const markdown_renderer_data *data)
{
	markdown_html_renderer_state *state;

	if (inline_render)
		return;

	state = data->opaque;

	while (state->toc_data.current_level > 0) {
		MARKDOWN_BUFPUTSL(ob, "</li>\n</ul>\n");
		state->toc_data.current_level--;
	}

	state->toc_data.header_count = 0;
}

markdown_renderer *
markdown_html_toc_renderer_new(int nesting_level)
{
	static const markdown_renderer cb_default = {
		NULL,

		NULL,
		NULL,
		toc_header,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,

		NULL,
		rndr_codespan,
		rndr_double_emphasis,
		rndr_emphasis,
		rndr_underline,
		rndr_highlight,
		rndr_quote,
		NULL,
		NULL,
		toc_link,
		rndr_triple_emphasis,
		rndr_strikethrough,
		rndr_superscript,
		NULL,
		NULL,
		NULL,

		NULL,
		rndr_normal_text,

		NULL,
		toc_finalize
	};

	markdown_html_renderer_state *state;
	markdown_renderer *renderer;

	/* Prepare the state pointer */
	state = markdown_malloc(sizeof(markdown_html_renderer_state));
	memset(state, 0x0, sizeof(markdown_html_renderer_state));

	state->toc_data.nesting_level = nesting_level;

	/* Prepare the renderer */
	renderer = markdown_malloc(sizeof(markdown_renderer));
	memcpy(renderer, &cb_default, sizeof(markdown_renderer));

	renderer->opaque = state;
	return renderer;
}

markdown_renderer *
markdown_html_renderer_new(markdown_html_flags render_flags, int nesting_level)
{
	static const markdown_renderer cb_default = {
		NULL,

		rndr_blockcode,
		rndr_blockquote,
		rndr_header,
		rndr_hrule,
		rndr_list,
		rndr_listitem,
		rndr_paragraph,
		rndr_table,
		rndr_table_header,
		rndr_table_body,
		rndr_tablerow,
		rndr_tablecell,
		rndr_footnotes,
		rndr_footnote_def,
		rndr_raw_block,

		rndr_autolink,
		rndr_codespan,
		rndr_double_emphasis,
		rndr_emphasis,
		rndr_underline,
		rndr_highlight,
		rndr_quote,
		rndr_image,
		rndr_linebreak,
		rndr_link,
		rndr_triple_emphasis,
		rndr_strikethrough,
		rndr_superscript,
		rndr_footnote_ref,
		rndr_math,
		rndr_raw_html,

		NULL,
		rndr_normal_text,

		NULL,
		NULL
	};

	markdown_html_renderer_state *state;
	markdown_renderer *renderer;

	/* Prepare the state pointer */
	state = markdown_malloc(sizeof(markdown_html_renderer_state));
	memset(state, 0x0, sizeof(markdown_html_renderer_state));

	state->flags = render_flags;
	state->toc_data.nesting_level = nesting_level;

	/* Prepare the renderer */
	renderer = markdown_malloc(sizeof(markdown_renderer));
	memcpy(renderer, &cb_default, sizeof(markdown_renderer));

	if (render_flags & MARKDOWN_HTML_SKIP_HTML || render_flags & MARKDOWN_HTML_ESCAPE)
		renderer->blockhtml = NULL;

	renderer->opaque = state;
	return renderer;
}

void
markdown_html_renderer_free(markdown_renderer *renderer)
{
	free(renderer->opaque);
	free(renderer);
}
