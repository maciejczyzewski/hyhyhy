CFLAGS = -g -O3 -ansi -pedantic -Wall -Wextra -Wno-unused-parameter -Isrc
PREFIX = /usr/local

ifneq ($(OS),Windows_NT)
	CFLAGS += -fPIC
endif

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

.PHONY:		all test test-pl clean

all:		libmarkdown.so markdown

# Libraries

libmarkdown.so: libmarkdown.so.3
	ln -f -s $^ $@

libmarkdown.so.3: $(MARKDOWN_SRC)
	$(CC) -shared $^ $(LDFLAGS) -o $@

libmarkdown.a: $(MARKDOWN_SRC)
	$(AR) rcs libmarkdown.a $^

# Executables

markdown: bin/markdown.o $(MARKDOWN_SRC)
	$(CC) $^ $(LDFLAGS) -o $@

# Perfect hashing

src/html_blocks.c: html_block_names.gperf
	gperf -L ANSI-C -N markdown_find_block_tag -c -C -E -S 1 --ignore-case -m100 $^ > $@

# Testing

test: markdown
	python test/runner.py

test-pl: markdown
	perl test/MarkdownTest_1.0.3/MarkdownTest.pl \
		--script=./markdown --testdir=test/MarkdownTest_1.0.3/Tests --tidy

# Housekeeping

clean:
	$(RM) src/*.o bin/*.o
	$(RM) libmarkdown.so libmarkdown.so.1 libmarkdown.a
	$(RM) markdown smartypants markdown.exe smartypants.exe

# Installing

install:
	install -m755 -d $(DESTDIR)$(PREFIX)/lib
	install -m755 -d $(DESTDIR)$(PREFIX)/bin
	install -m755 -d $(DESTDIR)$(PREFIX)/include

	install -m644 libmarkdown.* $(DESTDIR)$(PREFIX)/lib
	install -m755 markdown $(DESTDIR)$(PREFIX)/bin
	install -m755 smartypants $(DESTDIR)$(PREFIX)/bin

	install -m755 -d $(DESTDIR)$(PREFIX)/include/markdown
	install -m644 src/*.h $(DESTDIR)$(PREFIX)/include/markdown

# Generic object compilations

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/html_blocks.o: src/html_blocks.c
	$(CC) $(CFLAGS) -Wno-static-in-inline -c -o $@ $<
