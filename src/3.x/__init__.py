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

import os
import sys
import shutil

from rjsmin import jsmin
from rcssmin import cssmin

from hyhyhy.collector import collector
from hyhyhy.config import config
from hyhyhy.middleware import (num, prf)

class Cli:
    def build(self):
        if os.path.exists('build'):
            shutil.rmtree('build')

        if not os.path.exists('assets') \
            and not os.path.exists('sections') \
            and not os.path.exists(config.file):
            print (prf('FAIL'), 'Structure does not exist', '!')
            sys.exit(1)
            
        shutil.copytree('assets', 'build')

        with open(config.settings.get('core', 'build'), 'w') as build:
            build.write(collector.html())

        os.remove('build/index.jinja')

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

        print (prf('OK'), 'Saved in', config.settings.get('core', 'build'), '->',
               config.settings.get('head', 'title'))


    def create(self):
        if not os.path.exists('assets'):
            shutil.copytree(config.path[0] + 'assets', 'assets')
        else:
            print (prf('WARNING'), 'Path already exists assets/', '!')

        if not os.path.exists('sections'):
            shutil.copytree(config.path[0] + 'sections', 'sections')
        else:
            print (prf('WARNING'), 'Path already exists sections/', '!')

        if not os.path.exists('default.cfg'):
            shutil.copyfile(config.path[0] + 'default.cfg', 'default.cfg')
        else:
            print (prf('WARNING'), 'Path already exists default.cfg', '!')

        print (prf('OK'), 'New project created!')


    def status(self):
        print (prf('OK'), 'Structure of project', '[' + str(len(config.sections))
               + ' slides]')

        print (os.popen(''' find . -print 2>/dev/null | awk '!/\.$/ { \
            for (i=1; i<NF; i++) { \
                printf("%4s", "|") \
            } \
            print "-- "$NF \
        }' FS='/' ''').read())


def main():
    cli = Cli()

    if len(sys.argv) == 2 and sys.argv[1] == 'build':
        cli.build()
    elif len(sys.argv) == 2 and sys.argv[1] == 'create':
        cli.create()
    elif len(sys.argv) == 2 and sys.argv[1] == 'status':
        cli.status()
    else:
        print (__doc__)


if __name__ == '__main__':
    main()  

