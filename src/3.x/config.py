#!/usr/bin/python
# -*- coding: utf-8 -*-

import os
import configparser
import glob

from hyhyhy.utils import num, prf

path = [os.path.abspath(__file__ + '/../../lib/structure/') + '/',
        os.path.abspath(os.getcwd()) + '/']

sections = list(glob.glob('sections/*'))
default = 'default.cfg'

config = configparser.ConfigParser()
config.read(default)

sections.sort(key=num)