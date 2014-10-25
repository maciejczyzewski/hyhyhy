#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import configparser
import glob

from hyhyhy.middleware import num


class Config:
	def __init__(self, file):
		self.path = [os.path.abspath(__file__ + '/../../lib/structure/') + '/',
        			 os.path.abspath(os.getcwd()) + '/']

		self.settings = configparser.ConfigParser()
		self.settings.read(file)

		self.sections = list(glob.glob('sections/*'))
		self.sections.sort(key=num)

		self.file = file


config = Config('default.cfg')

