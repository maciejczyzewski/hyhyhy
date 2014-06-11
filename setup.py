import os
import sys

from setuptools import setup

pkgdir = {
    'hyhyhy': 'src/%s.x' % sys.version_info[0],
}

setup(
    name='hyhyhy',
    version='1.1.4',
    packages=['hyhyhy', 'lib'],
    package_dir=pkgdir,
    include_package_data=True,
    zip_safe=False,
    entry_points={
        "console_scripts": [
            "hyhyhy = hyhyhy:main",
        ]
    },
    install_requires=[
        'rjsmin',
        'rcssmin',
        'markdown',
        'jinja2',
        'watchdog',
    ],
    author='Maciej A. Czyzewski',
    author_email='maciejanthonyczyzewski@gmail.com',
    description='Presentation nano-framework',
    long_description="""\
Read the `README <https://github.com/MaciejCzyzewski/hyhyhy/blob/master/README.md>`_
for formatting instructions and more information.
""",
    license='MIT',
    keywords='presentation utilities tool framework',
    url='https://github.com/MaciejCzyzewski/hyhyhy',
    platforms=['any'],
    classifiers=[
        'Operating System :: OS Independent',
        'Development Status :: 3 - Alpha',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3.2',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Environment :: Console',
        'Environment :: Web Environment',
        'Topic :: Utilities',
        'Topic :: Multimedia :: Graphics :: Presentation',
        'Topic :: Text Processing :: Markup',
        'License :: OSI Approved :: MIT License',
    ],
)
