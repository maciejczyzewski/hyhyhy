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

import markdown
import jinja2

from hyhyhy.config import path, sections, default, config
from hyhyhy.utils import num, prf
from io import open


def parse(a=[], b=u'', c=u''):
    for i in sections:
        print prf(u'OK'), u'Parsing file', i, u'...'
        c = i.split(u'.')[-2].split(u'/')[-1]
        if i.split(u'.')[-1] == u'md':
            b = unicode(markdown.markdown(open(i, u'r').read()))
        elif i.split(u'.')[-1] == u'html':
            b = unicode(open(i, u'r').read())
        if config.has_option(u'sections', c):
            a.append([b, config.get(u'sections', c)])
        else:
            a.append([b, u' '])

    return a


def html():
    template = jinja2.Template(open(u'assets/index.jinja', u'r').read())

    templateVars = {u'title': unicode(config.get(u'head', u'title')),
                    u'description': unicode(config.get(u'head', u'description'
                    )), u'sections': parse()}

    return template.render(templateVars)