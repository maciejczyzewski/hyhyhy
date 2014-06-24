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

u"""
hyhyhy - Presentation nano-framework.

It's a tool for easily creating pure and 
simple HTML5 presentations or websites...

Usage:
  hyhyhy create
  hyhyhy build
  hyhyhy watch
  hyhyhy status
  hyhyhy (--h | --help)
  hyhyhy (--v | --version)

Options:
  -h --help     Show this screen.
  --version     Show version.
"""

from __future__ import with_statement
import os
import re
import sys
import shutil
import time

from rjsmin import jsmin
from rcssmin import cssmin
from watchdog.events import FileSystemEventHandler
from watchdog.observers import Observer
from docopt import docopt

from hyhyhy.collector import collector
from hyhyhy.config import config
from hyhyhy.middleware import (num, prf)
from io import open

base = os.path.dirname(os.path.abspath(__file__))

def version(filename=u'../lib/__init__.py'):
    with open(os.path.join(base, filename)) as initfile:
        for line in initfile.readlines():
            m = re.match(u"__version__ *= *['\"](.*)['\"]", line)

            if m:
                __version__ = m.group(1)

__version__ = version()

class Cli(object):

    class FileChangeHandler(FileSystemEventHandler):
        def on_any_event(self, event):
            Cli().build()

    def build(self):
        if os.path.exists(u'build'):
            shutil.rmtree(u'build')

        if not os.path.exists(u'assets') \
            and not os.path.exists(u'sections') \
            and not os.path.exists(config.file):
            print prf(u'FAIL'), u'Structure does not exist', u'!'
            sys.exit(1)
            
        shutil.copytree(u'assets', u'build')

        with open(config.settings.get(u'core', u'build'), u'w') as build:
            build.write(collector.html())

        os.remove(u'build/index.jinja')

        for (top, dirs, files) in os.walk(u'build/'):
            for nm in files:
                if os.path.join(top, nm).split(u'.')[-1] == u'js':
                    with open(os.path.join(top, nm)) as f:
                        file_str = f.read()
                    file_str = jsmin(file_str)
                    with open(os.path.join(top, nm), u'w') as f:
                        f.write(file_str)

                    print prf(u'OK'), u'Compressing file', nm, u'...'

                if os.path.join(top, nm).split(u'.')[-1] == u'css':
                    with open(os.path.join(top, nm)) as f:
                        file_str = f.read()
                    file_str = cssmin(file_str)
                    with open(os.path.join(top, nm), u'w') as f:
                        f.write(file_str)

                    print prf(u'OK'), u'Compressing file', nm, u'...'

        print prf(u'OK'), u'Saved in', config.settings.get(u'core', u'build'), u'->', config.settings.get(u'head', u'title')

    def watch(self):
        self.build()
        event_handler = self.FileChangeHandler()
        observer = Observer()
        for path in [u'assets', u'sections']:
            observer.schedule(event_handler, path, recursive=True)
        observer.start()

        try:
            while True:
                time.sleep(1)
        except KeyboardInterrupt:
            observer.stop()

        observer.join()

    def create(self):
        if not os.path.exists(u'assets'):
            shutil.copytree(config.path[0] + u'assets', u'assets')
        else:
            print prf(u'WARNING'), u'Path already exists assets/', u'!'

        if not os.path.exists(u'sections'):
            shutil.copytree(config.path[0] + u'sections', u'sections')
        else:
            print prf(u'WARNING'), u'Path already exists sections/', u'!'

        if not os.path.exists(u'default.cfg'):
            shutil.copyfile(config.path[0] + u'default.cfg', u'default.cfg')
        else:
            print prf(u'WARNING'), u'Path already exists default.cfg', u'!'

        print prf(u'OK'), u'New project created!'


    def status(self):
        print prf(u'OK'), u'Structure of project', u'[' + unicode(len(config.sections)) + u' slides]'

        print os.popen(u''' find . -print 2>/dev/null | awk '!/\.$/ { \
            for (i=1; i<NF; i++) { \
                printf("%4s", "|") \
            } \
            print "-- "$NF \
        }' FS='/' ''').read()


def main():
    cli = Cli()

    arguments = docopt(__doc__, version=__version__)

    if   arguments[u'build'] == True:
        cli.build()
    elif arguments[u'watch'] == True:
        cli.watch()
    elif arguments[u'create'] == True:
        cli.create()
    elif arguments[u'status'] == True:
        cli.status()
    else:
        print arguments


if __name__ == u'__main__':
    main()  

