#!/usr/bin/python
# -*- coding: utf-8 -*-

import os


def num(path):
    return int(os.path.splitext(os.path.basename(path))[0])


def prf(code):
    mode = {
        'OK':       '\033[92m[OK]\033[0m',
        'FAIL':     '\033[91m[FAIL]\033[0m',
        'INFO':     '\033[95m[INFO]\033[0m',
        'WARNING':  '\033[93m[WARNING]\033[0m',
        }

    return mode[str(code)]

