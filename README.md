<div align="center">
  <img src="https://raw.githubusercontent.com/MaciejCzyzewski/hyhyhy/master/screenshot-1.png"/>
</div>

# hyhyhy [![Build Status](https://travis-ci.org/MaciejCzyzewski/hyhyhy.png)](https://travis-ci.org/MaciejCzyzewski/hyhyhy) [![PyPI version](https://badge.fury.io/py/hyhyhy.png)](http://badge.fury.io/py/hyhyhy)

Presentation nano-framework.

## Introduction

It's a tool for easily creating pure and simple HTML5 presentations or websites.

Comes with a broad range of features including nested slides, markdown contents and a JavaScript API. It combines everything into a unified whole that you can use.

#### More reading:

- [Installation](#installation): Step-by-step instructions for getting hyhyhy running on your computer.
- [Usage](#usage): List of commands.
- [Configuration](#configuration): Explanation of configure the tool.
- [Presentation](#presentation): Explanation of use the generated project.
- [Dependencies](#dependencies): List of used dependencies.
- [Quickstart](#quickstart): Step-by-step instructions for creating new project.
- [Example](#example): Preview in action.
- [Supported browsers](#supported-browsers): Explanation of browser support and fallbacks.
- [Contributing](#contributing): Explanation of how you can join the project.
- [License](#license): Clarification of certain rules.

## Installation

Binary installers for the latest released version are available at the [Python
package index.](http://pypi.python.org/pypi/hyhyhy/)

```bash
$ pip install hyhyhy
```

You can create a new project by generating structure like this. Make sure that the destination folder does not exist because it will be overwritten.

```bash
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

<div align="center">
  <img src="https://raw.githubusercontent.com/MaciejCzyzewski/hyhyhy/master/screenshot-2.png"/>
</div>

### Build

This function should splice all your slides/sections in one presentation.
When you build your project it will generate a static version in the build folder that you can use. 

```bash
$ hyhyhy build
```

### Watch

Continously monitor the filesystem and wait for changes to rebuild to project automatically.

```bash
$ hyhyhy watch
```

### Create

Creates a default structure.

```bash
$ hyhyhy create
```

### Status

Show the structure of your project.

```bash
$ hyhyhy status
```

### Help

Displays a brief summary of the basic functions.

```bash
$ hyhyhy --help
```

## Configuration

For now, you can change the basic variables in the configuration file.

```properties
[head]
title = Example presentation by hyhyhy!
description = A little words...

[core]
build = build/index.html
```

You can also manipulate additional settings for 'section' tag in html.

```properties
[sections]
6 = data-bespoke-state="green" class="light"
```

The output for the above should be the following code. (for 6 slide)

```html
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
	* watchdog
	* docopt
- Javascript
	* prism.js
	* bespoke.js

## Quickstart

```bash
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

[![Gitter chat](https://badges.gitter.im/MaciejCzyzewski/hyhyhy.png)](https://gitter.im/MaciejCzyzewski/hyhyhy)

## License

See LICENSE file in this repository.

## Thanks

* Kim Thoenen ([@Chive](https://github.com/Chive))