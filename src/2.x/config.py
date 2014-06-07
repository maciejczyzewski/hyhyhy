#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import ConfigParser
import glob

from hyhyhy.utils import num, prf

path = [os.path.abspath(__file__ + u'/../../lib/structure/') + u'/',
        os.path.abspath(os.getcwdu()) + u'/']

sections = list(glob.glob(u'sections/*'))
default = u'default.cfg'

config = ConfigParser.ConfigParser()
config.read(default)

sections.sort(key=num)