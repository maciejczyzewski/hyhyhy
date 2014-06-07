#!/usr/bin/python
# -*- coding: utf-8 -*-

import os


def num(path):
    name = os.path.basename(path)
    (name, ext) = os.path.splitext(name)
    return int(name)


def prf(a):
    b = {
        u'OK': u'\033[92m[OK]\033[0m',
        u'FAIL': u'\033[91m[FAIL]\033[0m',
        u'INFO': u'\033[95m[INFO]\033[0m',
        u'WARNING': u'\033[93m[WARNING]\033[0m',
        }
    return b[unicode(a)]