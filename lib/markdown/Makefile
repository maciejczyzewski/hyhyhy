CFLAGS = -g -O3 -ansi -pedantic -Wall -Wextra -Wno-unused-parameter -Isrc

MARKDOWN_SRC=\
	src/autolink.o \
	src/buffer.o \
	src/document.o \
	src/escape.o \
	src/html.o \
	src/html_blocks.o \
	src/html_smartypants.o \
	src/stack.o \
	src/version.o

.PHONY:	all clean

all: markdown

# Executables

markdown: bin/markdown.o $(MARKDOWN_SRC)
	$(CC) $^ $(LDFLAGS) -o $@

# Perfect hashing

src/html_blocks.c: html_block_names.gperf
	gperf -L ANSI-C -N markdown_find_block_tag -c -C -E -S 1 --ignore-case -m100 $^ > $@

# Housekeeping

clean:
	$(RM) src/*.o bin/*.o
	$(RM) markdown

# Generic object compilations

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/html_blocks.o: src/html_blocks.c
	$(CC) $(CFLAGS) -Wno-static-in-inline -c -o $@ $<
