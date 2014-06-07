#!/usr/bin/python
# -*- coding: utf-8 -*-

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