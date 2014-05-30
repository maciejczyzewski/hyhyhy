<div align="center">
  <img src="https://raw.githubusercontent.com/MaciejCzyzewski/Hyhyhy/master/screenshot.png"/>
</div>

# Hyhyhy [![Build Status](https://travis-ci.org/MaciejCzyzewski/Hyhyhy.png)](https://travis-ci.org/MaciejCzyzewski/Hyhyhy)

hyhyhy.py — Presentation nano-framework.

## Installation

You can create a new project by generating structure like this. Make sure that the destination folder does not exist because it will be overwritten.

```
- assets/
	- master.css [style]
	- master.js [script]
- sections/
	- 1.html
	- 2.html
	...
	- n.html
default.cfg
hyhyhy.py
```

## Usage

### Build

This function should splice all your slides/sections in one presentation.
When you build your project it will generate a static version in the build folder that you can use. 

```
hyhyhy.py build
```

### Status

Show the structure of your project.

```
hyhyhy.py status
```

### Help

Displays a brief summary of the basic functions.

```
hyhyhy.py help
```

## Configuration

For now, you can change the basic variables in the configuration file.

```
[head]
charset = UTF-8
title = Example presentation by hyhyhy.py!

[core]
build = build/index.html
```

## Example 

Sample presentation is already in the project. But if you want you can see it live [by clicking this link.](https://dl.dropboxusercontent.com/u/103345209/Hyhyhy/index.html)

## Contributing

Please feel free to contribute to this project! Pull requests and feature requests welcome! :v:

## License

See LICENSE file in this repository.