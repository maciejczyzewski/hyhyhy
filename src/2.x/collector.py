#!/usr/bin/python
# -*- coding: utf-8 -*-

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
                html = markdown.markdown(open(file, u'r').read(), extensions=['markdown.extensions.fenced_code'])
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

