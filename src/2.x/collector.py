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

from hyhyhy.config import config
from hyhyhy.middleware import prf
from io import open


class Collector(object):
    def parse(self, content=[], html=u'', id=u''):
        for file in config.sections:
            print prf(u'OK'), u'Parsing file', file, u'...'

            id = file.split(u'.')[-2].split(u'/')[-1]

            if file.split(u'.')[-1] == u'md':
                html = markdown.markdown(open(file, u'r').read())
            elif file.split(u'.')[-1] == u'html':
                html = open(file, u'r').read()

            if config.settings.has_option(u'sections', id):
                content.append([html, config.settings.get(u'sections', id)])
            else:
                content.append([html, u' '])

        return content


    def html(self):
        template = jinja2.Template(open(u'assets/index.jinja', u'r').read())

        vars = {
            u'title':        config.settings.get(u'head', u'title'),
            u'description':  config.settings.get(u'head', u'description'),
            u'sections':     self.parse()
            }

        return template.render(vars)


collector = Collector()

