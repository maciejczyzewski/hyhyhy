#!/usr/bin/python
# -*- coding: utf-8 -*-

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
                html = markdown.markdown(open(file, 'r').read(), extensions=['markdown.extensions.fenced_code'])
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

