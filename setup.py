import os
import sys

from setuptools import setup

# Utility function to read the README file.
# Used for the long_description. It's nice, because now 1) we have a top level
# README file and 2) it's easier to type in the README file than to put a raw
# string in below ...
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

# Version of python
pkgdir = {'hyhyhy': 'src/%s.x' % sys.version_info[0]}

setup(
    name='hyhyhy',
    version='1.0.1',
    packages=['hyhyhy'],
    package_dir=pkgdir,
    package_data={
        'hyhyhy': ['structure/*.*', 'structure/*/*.*', 'structure/*/*/*.*']
    },
    entry_points={
        "console_scripts": [
            "hyhyhy = hyhyhy:main",
        ]
    },
    install_requires=['rjsmin', 'rcssmin', 'markdown', 'jinja2'],
    author='Maciej A. Czyzewski',
    author_email='maciejanthonyczyzewski@gmail.com',
    description=('Presentation nano-framework'),
    long_description=read('README.md'),
    license='MIT',
    keywords='presentation utilities tool framework',
    url='https://github.com/MaciejCzyzewski/hyhyhy',
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Topic :: Utilities',
        'License :: OSI Approved :: MIT License',
    ],
)
