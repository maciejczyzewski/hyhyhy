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


class Collector:
    def parse(self, content=[], html='', id=''):
        for file in config.sections:
            print (prf('OK'), 'Parsing file', file, '...')

            id = file.split('.')[-2].split('/')[-1]

            if file.split('.')[-1] == 'md':
                html = markdown.markdown(open(file, 'r').read())
            elif file.split('.')[-1] == 'html':
                html = open(file, 'r').read()

            if config.settings.has_option('sections', id):
                content.append([html, config.settings.get('sections', id)])
            else:
                content.append([html, ' '])

        return content


    def html(self):
        template = jinja2.Template(open('assets/index.jinja', 'r').read())

        vars = {
            'title':        config.settings.get('head', 'title'),
            'description':  config.settings.get('head', 'description'),
            'sections':     self.parse()
            }

        return template.render(vars)


collector = Collector()

