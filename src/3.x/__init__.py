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

import sys
import os

import configparser
import glob
import shutil

from rjsmin import jsmin
from rcssmin import cssmin

import markdown
import jinja2

__version__ = '1.0.1'

__help__ = '''
    hyhyhy - Presentation nano-framework.                                 [v ''' + __version__ + ''']
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
        'OK': '\033[92m[OK]\033[0m',
        'FAIL': '\033[91m[FAIL]\033[0m',
        'INFO': '\033[95m[INFO]\033[0m',
        'WARNING': '\033[93m[WARNING]\033[0m',
    }
    return b[str(a)]


path = [os.path.abspath(__file__ + '/../structure/') + '/', os.path.abspath(os.getcwd()) + '/']

sections = list(glob.glob('sections/*'))
default = 'default.cfg'

config = configparser.ConfigParser()
config.read(default)

sections.sort(key=num)


def get_sections(a=[], b='', c=''):
    global sections

    for i in sections:
        print(prf('OK'), "Parsing file", i, "...")
        c = (i.split('.')[-2]).split('/')[-1]
        if i.split('.')[-1] == "md":
            b = str(markdown.markdown(open(i, 'r').read()))
        elif i.split('.')[-1] == "html":
            b = str(open(i, 'r').read())
        if config.has_option('sections', c):
            a.append([b, config.get('sections', c)])
        else:
            a.append([b, ' '])

    return a


def get_html():
    global config

    template = jinja2.Template(open("assets/index.jinja", 'r').read())

    templateVars = { "title" : str(config.get('head', 'title')),
                     "description" : str(config.get('head', 'description')),
                     "sections": get_sections() }

    return template.render(templateVars)


def init_build():
    global config, path

    if os.path.exists(path[1] + 'build'):
        shutil.rmtree(path[1] + 'build')

    shutil.copytree(path[1] + 'assets', path[1] + 'build')

    with open(config.get('core', 'build'), 'w') as build:
        build.write(get_html())

    os.remove(path[1] + 'build/index.jinja')

    for top, dirs, files in os.walk('build/'):
        for nm in files:  
            if os.path.join(top, nm).split('.')[-1] == "js":
                with open(os.path.join(top, nm)) as f:
                    file_str = f.read()
                file_str = jsmin(file_str)
                with open(os.path.join(top, nm), "w") as f:
                    f.write(file_str)

                print(prf('OK'), "Compressing file", nm, "..." )
            if os.path.join(top, nm).split('.')[-1] == "css":
                with open(os.path.join(top, nm)) as f:
                    file_str = f.read()
                file_str = cssmin(file_str)
                with open(os.path.join(top, nm), "w") as f:
                    f.write(file_str)

                print(prf('OK'), "Compressing file", nm, "..." )

    print(prf('OK'), "Saved in", config.get('core', 'build'), "->", config.get('head', 'title'))


def init_create():
    if not os.path.exists(path[1] + 'assets'):
        shutil.copytree(path[0] + 'assets', path[1] + 'assets')
    else:
        print(prf('WARNING'), "Path already exists assets/", "!")

    if not os.path.exists(path[1] + 'sections'):
        shutil.copytree(path[0] + 'sections', path[1] + 'sections')
    else:
        print(prf('WARNING'), "Path already exists sections/", "!")

    if not os.path.exists(path[1] + 'default.cfg'):
        shutil.copyfile(path[0] + 'default.cfg', path[1] + 'default.cfg')
    else:
        print(prf('WARNING'), "Path already exists default.cfg", "!")

    print(prf('OK'), "New project created!")


def init_status():
    global sections

    print(prf('OK'), "Structure of project", "[" + str(len(sections)) + " slides]")

    print(os.popen(''' find . -print 2>/dev/null | awk '!/\.$/ { \
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
        print(__help__)
