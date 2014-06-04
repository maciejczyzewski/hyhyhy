import os
import sys

from setuptools import setup

# Utility function to read the README file.
# Used for the long_description. It's nice, because now 1) we have a top level
# README file and 2) it's easier to type in the README file than to put a raw
# string in below ...
def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

def tree(fname, sname):
    datadir, tree = os.path.join(fname, sname), []
    for d,folders,files in os.walk(datadir):
        for f in files:
            tree.append(os.path.join(d, f)[len(fname) + 1:])
    return tree

# Version of python
pkgdir = {
    'hyhyhy': 'src/%s.x' % sys.version_info[0],
}

setup(
    name='hyhyhy',
    version='1.0.7',
    packages=['hyhyhy'],
    package_dir=pkgdir,
    package_data={
        'hyhyhy': tree(pkgdir['hyhyhy'], 'structure')
    },
    include_package_data=True,
    entry_points={
        "console_scripts": [
            "hyhyhy = hyhyhy:main",
        ]
    },
    install_requires=['rjsmin', 'rcssmin', 'markdown', 'jinja2'],
    author='Maciej A. Czyzewski',
    author_email='maciejanthonyczyzewski@gmail.com',
    description=('Presentation nano-framework'),
    long_description="""\
Read the `README <https://github.com/MaciejCzyzewski/hyhyhy/blob/master/README.md>`_
for formatting instructions and more information.
""",
    license='MIT',
    keywords='presentation utilities tool framework',
    url='https://github.com/MaciejCzyzewski/hyhyhy',
    platforms=['any'],
    classifiers=[
        'Development Status :: 3 - Alpha',
        'Topic :: Utilities',
        'License :: OSI Approved :: MIT License',
    ],
)
