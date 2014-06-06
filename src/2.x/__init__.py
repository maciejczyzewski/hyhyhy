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

from __future__ import with_statement
import sys
import os

import ConfigParser
import glob
import shutil

from rjsmin import jsmin
from rcssmin import cssmin

import markdown
import jinja2
from io import open

__version__ = u'1.0.8'

__help__ = u'''
    hyhyhy - Presentation nano-framework.                                 [v ''' + __version__ + u''']
        hyhyhy build     -     This function should splice all your 
                               slides/sections in one presentation.
        hyhyhy create    -     Creates a default structure.
        hyhyhy status    -     Show the structure of your project.
        hyhyhy help      -     Displays a brief summary of the basic functions.
    '''


def num(path):
    name = os.path.basename(path)
    name, ext = os.path.splitext(name)
    return int(name)


def prf(a):
    b = {
        u'OK': u'\033[92m[OK]\033[0m',
        u'FAIL': u'\033[91m[FAIL]\033[0m',
        u'INFO': u'\033[95m[INFO]\033[0m',
        u'WARNING': u'\033[93m[WARNING]\033[0m',
    }
    return b[unicode(a)]


path = [os.path.abspath(__file__ + u'/../../lib/structure/') + u'/', os.path.abspath(os.getcwdu()) + u'/']

sections = list(glob.glob(u'sections/*'))
default = u'default.cfg'

config = ConfigParser.ConfigParser()
config.read(default)

sections.sort(key=num)


def get_sections(a=[], b=u'', c=u''):
    global sections

    for i in sections:
        print prf(u'OK'), u"Parsing file", i, u"..."
        c = (i.split(u'.')[-2]).split(u'/')[-1]
        if i.split(u'.')[-1] == u"md":
            b = unicode(markdown.markdown(open(i, u'r').read()))
        elif i.split(u'.')[-1] == u"html":
            b = unicode(open(i, u'r').read())
        if config.has_option(u'sections', c):
            a.append([b, config.get(u'sections', c)])
        else:
            a.append([b, u' '])

    return a


def get_html():
    global config

    template = jinja2.Template(open(u"assets/index.jinja", u'r').read())

    templateVars = { u"title" : config.get(u'head', u'title').decode('utf-8'),
                     u"description" : config.get(u'head', u'description').decode('utf-8'),
                     u"sections": get_sections() }

    return template.render(templateVars)


def init_build():
    global config, path

    if os.path.exists(path[1] + u'build'):
        shutil.rmtree(path[1] + u'build')

    shutil.copytree(path[1] + u'assets', path[1] + u'build')

    with open(config.get(u'core', u'build'), u'w') as build:
        build.write(get_html())

    os.remove(path[1] + u'build/index.jinja')

    for top, dirs, files in os.walk(u'build/'):
        for nm in files:  
            if os.path.join(top, nm).split(u'.')[-1] == u"js":
                with open(os.path.join(top, nm)) as f:
                    file_str = f.read()
                file_str = jsmin(file_str)
                with open(os.path.join(top, nm), u"w") as f:
                    f.write(file_str)

                print prf(u'OK'), u"Compressing file", nm, u"..."
            if os.path.join(top, nm).split(u'.')[-1] == u"css":
                with open(os.path.join(top, nm)) as f:
                    file_str = f.read()
                file_str = cssmin(file_str)
                with open(os.path.join(top, nm), u"w") as f:
                    f.write(file_str)

                print prf(u'OK'), u"Compressing file", nm, u"..."

    print prf(u'OK'), u"Saved in", config.get(u'core', u'build'), u"->", config.get(u'head', u'title')


def init_create():
    if not os.path.exists(path[1] + u'assets'):
        shutil.copytree(path[0] + u'assets', path[1] + u'assets')
    else:
        print prf(u'WARNING'), u"Path already exists assets/", u"!"

    if not os.path.exists(path[1] + u'sections'):
        shutil.copytree(path[0] + u'sections', path[1] + u'sections')
    else:
        print prf(u'WARNING'), u"Path already exists sections/", u"!"

    if not os.path.exists(path[1] + u'default.cfg'):
        shutil.copyfile(path[0] + u'default.cfg', path[1] + u'default.cfg')
    else:
        print prf(u'WARNING'), u"Path already exists default.cfg", u"!"

    print prf(u'OK'), u"New project created!"


def init_status():
    global sections

    print prf(u'OK'), u"Structure of project", u"[" + unicode(len(sections)) + u" slides]"

    print os.popen(u''' find . -print 2>/dev/null | awk '!/\.$/ { \
        for (i=1; i<NF; i++) { \
            printf("%4s", "|") \
        } \
        print "-- "$NF \
    }' FS='/' ''').read()


def main():
    if len(sys.argv) == 2 and sys.argv[1] == u'build':
        init_build()
    elif len(sys.argv) == 2 and sys.argv[1] == u'create':
        init_create()
    elif len(sys.argv) == 2 and sys.argv[1] == u'status':
        init_status()
    else:
        print __help__
