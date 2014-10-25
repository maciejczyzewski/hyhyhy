#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import ConfigParser
import glob

from hyhyhy.middleware import num


class Config(object):
	def __init__(self, file):
		self.path = [os.path.abspath(__file__ + u'/../../lib/structure/') + u'/',
        			 os.path.abspath(os.getcwdu()) + u'/']

		self.settings = ConfigParser.ConfigParser()
		self.settings.read(file)

		self.sections = list(glob.glob(u'sections/*'))
		self.sections.sort(key=num)

		self.file = file


config = Config(u'default.cfg')

