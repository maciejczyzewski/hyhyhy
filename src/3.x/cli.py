#!/usr/bin/python
# -*- coding: utf-8 -*-

#
# hyhyhy - https://github.com/MaciejCzyzewski/hyhyhy
#
# The MIT License (MIT)
#
# Copyright (c) 2014 Maciej A. Czyzewski
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
# the Software, and to permit persons to whom the Software is furnished to do so,
# subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
# COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
# IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
#
# Author: Maciej A. Czyzewski <maciejanthonyczyzewski@gmail.com>
#

"""
hyhyhy CLI

Usage:
  hyhyhy create
  hyhyhy build
  hyhyhy status
  hyhyhy help
  hyhyhy -h | --help
  hyhyhy -V | --version

Options:
  -h, --help             Help information.
  -V, --version          Show version.
"""

import sys
import os

import shutil

from rjsmin import jsmin
from rcssmin import cssmin

from hyhyhy.get import sections, html
from hyhyhy.config import path, sections, default, config
from hyhyhy.utils import num, prf


def init_build():
    if os.path.exists(path[1] + 'build'):
        shutil.rmtree(path[1] + 'build')

    shutil.copytree(path[1] + 'assets', path[1] + 'build')

    with open(config.get('core', 'build'), 'w') as build:
        build.write(html())

    os.remove(path[1] + 'build/index.jinja')

    for (top, dirs, files) in os.walk('build/'):
        for nm in files:
            if os.path.join(top, nm).split('.')[-1] == 'js':
                with open(os.path.join(top, nm)) as f:
                    file_str = f.read()
                file_str = jsmin(file_str)
                with open(os.path.join(top, nm), 'w') as f:
                    f.write(file_str)

                print (prf('OK'), 'Compressing file', nm, '...')
            if os.path.join(top, nm).split('.')[-1] == 'css':
                with open(os.path.join(top, nm)) as f:
                    file_str = f.read()
                file_str = cssmin(file_str)
                with open(os.path.join(top, nm), 'w') as f:
                    f.write(file_str)

                print (prf('OK'), 'Compressing file', nm, '...')

    print (prf('OK'), 'Saved in', config.get('core', 'build'), '->',
           config.get('head', 'title'))


def init_create():
    if not os.path.exists(path[1] + 'assets'):
        shutil.copytree(path[0] + 'assets', path[1] + 'assets')
    else:
        print (prf('WARNING'), 'Path already exists assets/', '!')

    if not os.path.exists(path[1] + 'sections'):
        shutil.copytree(path[0] + 'sections', path[1] + 'sections')
    else:
        print (prf('WARNING'), 'Path already exists sections/', '!')

    if not os.path.exists(path[1] + 'default.cfg'):
        shutil.copyfile(path[0] + 'default.cfg', path[1] + 'default.cfg')
    else:
        print (prf('WARNING'), 'Path already exists default.cfg', '!')

    print (prf('OK'), 'New project created!')


def init_status():
    print (prf('OK'), 'Structure of project', '[' + str(len(sections))
           + ' slides]')

    print (os.popen(''' find . -print 2>/dev/null | awk '!/\.$/ { \
        for (i=1; i<NF; i++) { \
            printf("%4s", "|") \
        } \
        print "-- "$NF \
    }' FS='/' ''').read())


def main():
    if len(sys.argv) == 2 and sys.argv[1] == 'build':
        init_build()
    elif len(sys.argv) == 2 and sys.argv[1] == 'create':
        init_create()
    elif len(sys.argv) == 2 and sys.argv[1] == 'status':
        init_status()
    else:
        print (__doc__)


if __name__ == '__main__':
    main()  