#!/usr/bin/python
# -*- coding: utf-8 -*-

import os


def num(path):
    name = os.path.basename(path)
    (name, ext) = os.path.splitext(name)
    return int(name)


def prf(a):
    b = {
        'OK': '\033[92m[OK]\033[0m',
        'FAIL': '\033[91m[FAIL]\033[0m',
        'INFO': '\033[95m[INFO]\033[0m',
        'WARNING': '\033[93m[WARNING]\033[0m',
        }
    return b[str(a)]