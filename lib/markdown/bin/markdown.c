#include "document.h"
#include "html.h"

#include "common.h"
/*#include <time.h>*/


/* FEATURES INFO / DEFAULTS */

enum renderer_type {
	RENDERER_HTML,
	RENDERER_HTML_TOC
};

struct extension_category_info {
	unsigned int flags;
	const char *option_name;
	const char *label;
};

struct extension_info {
	unsigned int flag;
	const char *option_name;
	const char *description;
};

struct html_flag_info {
	unsigned int flag;
	const char *option_name;
	const char *description;
};

static struct extension_category_info categories_info[] = {
	{MARKDOWN_EXT_BLOCK, "block", "Block extensions"},
	{MARKDOWN_EXT_SPAN, "span", "Span extensions"},
	{MARKDOWN_EXT_FLAGS, "flags", "Other flags"},
	{MARKDOWN_EXT_NEGATIVE, "negative", "Negative flags"},
};

static struct extension_info extensions_info[] = {
	{MARKDOWN_EXT_TABLES, "tables", "Parse PHP-Markdown style tables."},
	{MARKDOWN_EXT_FENCED_CODE, "fenced-code", "Parse fenced code blocks."},
	{MARKDOWN_EXT_FOOTNOTES, "footnotes", "Parse footnotes."},

	{MARKDOWN_EXT_AUTOLINK, "autolink", "Automatically turn safe URLs into links."},
	{MARKDOWN_EXT_STRIKETHROUGH, "strikethrough", "Parse ~~stikethrough~~ spans."},
	{MARKDOWN_EXT_UNDERLINE, "underline", "Parse _underline_ instead of emphasis."},
	{MARKDOWN_EXT_HIGHLIGHT, "highlight", "Parse ==highlight== spans."},
	{MARKDOWN_EXT_QUOTE, "quote", "Render \"quotes\" as <q>quotes</q>."},
	{MARKDOWN_EXT_SUPERSCRIPT, "superscript", "Parse super^script."},
	{MARKDOWN_EXT_MATH, "math", "Parse TeX $$math$$ syntax, Kramdown style."},

	{MARKDOWN_EXT_NO_INTRA_EMPHASIS, "disable-intra-emphasis", "Disable emphasis_between_words."},
	{MARKDOWN_EXT_SPACE_HEADERS, "space-headers", "Require a space after '#' in headers."},
	{MARKDOWN_EXT_MATH_EXPLICIT, "math-explicit", "Instead of guessing by context, parse $inline math$ and $$always block math$$ (requires --math)."},

	{MARKDOWN_EXT_DISABLE_INDENTED_CODE, "disable-indented-code", "Don't parse indented code blocks."},
};

static struct html_flag_info html_flags_info[] = {
	{MARKDOWN_HTML_SKIP_HTML, "skip-html", "Strip all HTML tags."},
	{MARKDOWN_HTML_ESCAPE, "escape", "Escape all HTML."},
	{MARKDOWN_HTML_HARD_WRAP, "hard-wrap", "Render each linebreak as <br>."},
	{MARKDOWN_HTML_USE_XHTML, "xhtml", "Render XHTML."},
};

static const char *category_prefix = "all-";
static const char *negative_prefix = "no-";

#define DEF_IUNIT 1024
#define DEF_OUNIT 64
#define DEF_MAX_NESTING 16


/* PRINT HELP */

void
print_help(const char *basename)
{
	size_t i;
	size_t e;

	/* usage */
	printf("Usage: %s [OPTION]... [FILE]\n\n", basename);

	/* description */
	printf("Process the Markdown in FILE (or standard input) and render it to standard output, using the Markdown library. "
	       "Parsing and rendering can be customized through the options below. The default is to parse pure markdown and output HTML.\n\n");

	/* main options */
	printf("Main options:\n");
	print_option('n', "max-nesting=N", "Maximum level of block nesting parsed. Default is " str(DEF_MAX_NESTING) ".");
	print_option('t', "toc-level=N", "Maximum level for headers included in the TOC. Zero disables TOC (the default).");
	print_option(  0, "html", "Render (X)HTML. The default.");
	print_option(  0, "html-toc", "Render the Table of Contents in (X)HTML.");
	print_option('T', "time", "Show time spent in rendering.");
	print_option('i', "input-unit=N", "Reading block size. Default is " str(DEF_IUNIT) ".");
	print_option('o', "output-unit=N", "Writing block size. Default is " str(DEF_OUNIT) ".");
	print_option('h', "help", "Print this help text.");
	print_option('v', "version", "Print Markdown version.");
	printf("\n");

	/* extensions */
	for (i = 0; i < count_of(categories_info); i++) {
		struct extension_category_info *category = categories_info+i;
		printf("%s (--%s%s):\n", category->label, category_prefix, category->option_name);
		for (e = 0; e < count_of(extensions_info); e++) {
			struct extension_info *extension = extensions_info+e;
			if (extension->flag & category->flags) {
				print_option(  0, extension->option_name, extension->description);
			}
		}
		printf("\n");
	}

	/* html-specific */
	printf("HTML-specific options:\n");
	for (i = 0; i < count_of(html_flags_info); i++) {
		struct html_flag_info *html_flag = html_flags_info+i;
		print_option(  0, html_flag->option_name, html_flag->description);
	}
	printf("\n");

	/* ending */
	printf("Flags and extensions can be negated by prepending 'no' to them, as in '--no-tables', '--no-span' or '--no-escape'. "
	       "Options are processed in order, so in case of contradictory options the last specified stands.\n\n");

	printf("When FILE is '-', read standard input. If no FILE was given, read standard input. Use '--' to signal end of option parsing. "
	       "Exit status is 0 if no errors occurred, 1 with option parsing errors, 4 with memory allocation errors or 5 with I/O errors.\n\n");
}


/* OPTION PARSING */

struct option_data {
	char *basename;
	int done;

	/* time reporting */
	int show_time;

	/* I/O */
	size_t iunit;
	size_t ounit;
	const char *filename;

	/* renderer */
	enum renderer_type renderer;
	int toc_level;
	markdown_html_flags html_flags;

	/* parsing */
	markdown_extensions extensions;
	size_t max_nesting;
};

int
parse_short_option(char opt, char *next, void *opaque)
{
	struct option_data *data = opaque;
	long int num;
	int isNum = next ? parseint(next, &num) : 0;

	if (opt == 'h') {
		print_help(data->basename);
		data->done = 1;
		return 0;
	}

	if (opt == 'v') {
		print_version();
		data->done = 1;
		return 0;
	}

	if (opt == 'T') {
		data->show_time = 1;
		return 1;
	}

	/* options requiring value */
	/* FIXME: add validation */

	if (opt == 'n' && isNum) {
		data->max_nesting = num;
		return 2;
	}

	if (opt == 't' && isNum) {
		data->toc_level = num;
		return 2;
	}

	if (opt == 'i' && isNum) {
		data->iunit = num;
		return 2;
	}

	if (opt == 'o' && isNum) {
		data->ounit = num;
		return 2;
	}

	fprintf(stderr, "Wrong option '-%c' found.\n", opt);
	return 0;
}

int
parse_category_option(char *opt, struct option_data *data)
{
	size_t i;
	const char *name = strprefix(opt, category_prefix);
	if (!name) return 0;

	for (i = 0; i < count_of(categories_info); i++) {
		struct extension_category_info *category = &categories_info[i];
		if (strcmp(name, category->option_name)==0) {
			data->extensions |= category->flags;
			return 1;
		}
	}

	return 0;
}

int
parse_flag_option(char *opt, struct option_data *data)
{
	size_t i;

	for (i = 0; i < count_of(extensions_info); i++) {
		struct extension_info *extension = &extensions_info[i];
		if (strcmp(opt, extension->option_name)==0) {
			data->extensions |= extension->flag;
			return 1;
		}
	}

	for (i = 0; i < count_of(html_flags_info); i++) {
		struct html_flag_info *html_flag = &html_flags_info[i];
		if (strcmp(opt, html_flag->option_name)==0) {
			data->html_flags |= html_flag->flag;
			return 1;
		}
	}

	return 0;
}

int
parse_negative_option(char *opt, struct option_data *data)
{
	size_t i;
	const char *name = strprefix(opt, negative_prefix);
	if (!name) return 0;

	for (i = 0; i < count_of(categories_info); i++) {
		struct extension_category_info *category = &categories_info[i];
		if (strcmp(name, category->option_name)==0) {
			data->extensions &= ~(category->flags);
			return 1;
		}
	}

	for (i = 0; i < count_of(extensions_info); i++) {
		struct extension_info *extension = &extensions_info[i];
		if (strcmp(name, extension->option_name)==0) {
			data->extensions &= ~(extension->flag);
			return 1;
		}
	}

	for (i = 0; i < count_of(html_flags_info); i++) {
		struct html_flag_info *html_flag = &html_flags_info[i];
		if (strcmp(name, html_flag->option_name)==0) {
			data->html_flags &= ~(html_flag->flag);
			return 1;
		}
	}

	return 0;
}

int
parse_long_option(char *opt, char *next, void *opaque)
{
	struct option_data *data = opaque;
	long int num;
	int isNum = next ? parseint(next, &num) : 0;

	if (strcmp(opt, "help")==0) {
		print_help(data->basename);
		data->done = 1;
		return 0;
	}

	if (strcmp(opt, "version")==0) {
		print_version();
		data->done = 1;
		return 0;
	}

	if (strcmp(opt, "time")==0) {
		data->show_time = 1;
		return 1;
	}

	/* FIXME: validation */

	if (strcmp(opt, "max-nesting")==0 && isNum) {
		data->max_nesting = num;
		return 2;
	}
	if (strcmp(opt, "toc-level")==0 && isNum) {
		data->toc_level = num;
		return 2;
	}
	if (strcmp(opt, "input-unit")==0 && isNum) {
		data->iunit = num;
		return 2;
	}
	if (strcmp(opt, "output-unit")==0 && isNum) {
		data->ounit = num;
		return 2;
	}

	if (strcmp(opt, "html")==0) {
		data->renderer = RENDERER_HTML;
		return 1;
	}
	if (strcmp(opt, "html-toc")==0) {
		data->renderer = RENDERER_HTML_TOC;
		return 1;
	}

	if (parse_category_option(opt, data) || parse_flag_option(opt, data) || parse_negative_option(opt, data))
		return 1;

	fprintf(stderr, "Wrong option '--%s' found.\n", opt);
	return 0;
}

int
parse_argument(int argn, char *arg, int is_forced, void *opaque)
{
	struct option_data *data = opaque;

	if (argn == 0) {
		/* Input file */
		if (strcmp(arg, "-")!=0 || is_forced) data->filename = arg;
		return 1;
	}

	fprintf(stderr, "Too many arguments.\n");
	return 0;
}


/* MAIN LOGIC */

int
main(int argc, char **argv)
{
	struct option_data data;
	/*struct timespec start, end;*/
	FILE *file = stdin;
	markdown_buffer *ib, *ob;
	markdown_renderer *renderer = NULL;
	void (*renderer_free)(markdown_renderer *) = NULL;
	markdown_document *document;

	/* Parse options */
	data.basename = argv[0];
	data.done = 0;
	data.show_time = 0;
	data.iunit = DEF_IUNIT;
	data.ounit = DEF_OUNIT;
	data.filename = NULL;
	data.renderer = RENDERER_HTML;
	data.toc_level = 0;
	data.html_flags = 0;
	data.extensions = 0;
	data.max_nesting = DEF_MAX_NESTING;

	argc = parse_options(argc, argv, parse_short_option, parse_long_option, parse_argument, &data);
	if (data.done) return 0;
	if (!argc) return 1;

	/* Open input file, if needed */
	if (data.filename) {
		file = fopen(data.filename, "r");
		if (!file) {
			fprintf(stderr, "Unable to open input file \"%s\": %s\n", data.filename, strerror(errno));
			return 5;
		}
	}

	/* Read everything */
	ib = markdown_buffer_new(data.iunit);

	while (!feof(file)) {
		if (ferror(file)) {
			fprintf(stderr, "I/O errors found while reading input.\n");
			return 5;
		}
		markdown_buffer_grow(ib, ib->size + data.iunit);
		ib->size += fread(ib->data + ib->size, 1, data.iunit, file);
	}

	if (file != stdin) fclose(file);

	/* Create the renderer */
	switch (data.renderer) {
		case RENDERER_HTML:
			renderer = markdown_html_renderer_new(data.html_flags, data.toc_level);
			renderer_free = markdown_html_renderer_free;
			break;
		case RENDERER_HTML_TOC:
			renderer = markdown_html_toc_renderer_new(data.toc_level);
			renderer_free = markdown_html_renderer_free;
			break;
	};

	/* Perform Markdown rendering */
	ob = markdown_buffer_new(data.ounit);
	document = markdown_document_new(renderer, data.extensions, data.max_nesting);

	/*clock_gettime(CLOCK_MONOTONIC, &start);*/
	markdown_document_render(document, ob, ib->data, ib->size);
	/*clock_gettime(CLOCK_MONOTONIC, &end);*/

	/* Write the result to stdout */
	(void)fwrite(ob->data, 1, ob->size, stdout);

	/* Show rendering time */
	if (data.show_time) {
		/*TODO: enable this
		long long elapsed = (end.tv_sec - start.tv_sec)*1e9 + (end.tv_nsec - start.tv_nsec);
		if (elapsed < 1e9)
			fprintf(stderr, "Time spent on rendering: %.2f ms.\n", ((double)elapsed)/1e6);
		else
			fprintf(stderr, "Time spent on rendering: %.3f s.\n", ((double)elapsed)/1e9);
		*/
	}

	/* Cleanup */
	markdown_buffer_free(ib);
	markdown_buffer_free(ob);

	markdown_document_free(document);
	renderer_free(renderer);

	if (ferror(stdout)) {
		fprintf(stderr, "I/O errors found while writing output.\n");
		return 5;
	}

	return 0;
}
