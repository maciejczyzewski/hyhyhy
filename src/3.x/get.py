#!/usr/bin/python
# -*- coding: utf-8 -*-

import markdown
import jinja2

from hyhyhy.config import path, sections, default, config
from hyhyhy.utils import num, prf


def parse(a=[], b='', c=''):
    for i in sections:
        print (prf('OK'), 'Parsing file', i, '...')
        c = i.split('.')[-2].split('/')[-1]
        if i.split('.')[-1] == 'md':
            b = str(markdown.markdown(open(i, 'r').read()))
        elif i.split('.')[-1] == 'html':
            b = str(open(i, 'r').read())
        if config.has_option('sections', c):
            a.append([b, config.get('sections', c)])
        else:
            a.append([b, ' '])

    return a


def html():
    template = jinja2.Template(open('assets/index.jinja', 'r').read())

    templateVars = {'title': str(config.get('head', 'title')),
                    'description': str(config.get('head', 'description'
                    )), 'sections': parse()}

    return template.render(templateVars)