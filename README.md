<div align="center">
  <img src="https://raw.githubusercontent.com/MaciejCzyzewski/hyhyhy/master/screenshot.png"/>
</div>

# hyhyhy [![Build Status](https://travis-ci.org/MaciejCzyzewski/hyhyhy.png)](https://travis-ci.org/MaciejCzyzewski/hyhyhy) [![PyPI version](https://badge.fury.io/py/hyhyhy.png)](http://badge.fury.io/py/hyhyhy)

Presentation nano-framework.

## Installation

Binary installers for the latest released version are available at the [Python
package index.](http://pypi.python.org/pypi/hyhyhy/)

```
$ pip install hyhyhy
```

You can create a new project by generating structure like this. Make sure that the destination folder does not exist because it will be overwritten.

```
|-- assets
|   |-- index.jinja
|   |-- scripts
|   |   |-- main.js
|   |-- styles
|   |   |-- main.css
|-- sections
|   |-- 1.html
|   |-- 2.md
|   |-- ...
|   |-- n.html
|-- default.cfg
```

## Usage

### Build

This function should splice all your slides/sections in one presentation.
When you build your project it will generate a static version in the build folder that you can use. 

```
$ hyhyhy build
```

### Create

Creates a default structure.

```
$ hyhyhy create
```

### Status

Show the structure of your project.

```
$ hyhyhy status
```

### Help

Displays a brief summary of the basic functions.

```
$ hyhyhy help
```

## Configuration

For now, you can change the basic variables in the configuration file.

```
[head]
title = Example presentation by hyhyhy!
description = A little words...

[core]
build = build/index.html
```

You can also manipulate additional settings for 'section' tag in html.

```
[sections]
5 = data-bespoke-state="green" class="light"
```

The output for the above should be the following code. (for 5 slide)

```
<section data-bespoke-state="green" class="light">...</section>
```

## Presentation

- Press `left arrow` and `right arrow` to navigate.
- Press `h` to launch fullscreen.
- Press `ESC` to exit fullscreen mode.
- Browser zooming is supported.
- Touch events are supported.

## Dependencies

- Python (>= 2.7.0)
	* rjsmin
	* rcssmin
	* markdown
	* jinja2
- Javascript
	* prism.js
	* bespoke.js

## Quickstart

```
$ pip install hyhyhy
$ mkdir new_empty_presentation
$ cd new_empty_presentation
$ hyhyhy create
$ hyhyhy build
```

## Example 

Sample presentation is already in the project. But if you want you can see it live [by clicking this link.](http://maciejczyzewski.github.io/hyhyhy/)

## Supported browsers

- Firefox 2+
- Safari 3+
- Opera 9.64+
- Chrome
- IE9, IE10, IE11

## Contributing

Please feel free to contribute to this project! Pull requests and feature requests welcome! :v:

## License

See LICENSE file in this repository.