<div align="center">
  <img src="https://dl.dropboxusercontent.com/u/103345209/Screenshots/Screenshot%202014-12-14%2021.40.38.png"/>
</div>

# hyhyhy [![Gem Version](https://badge.fury.io/rb/hyhyhy.svg)](http://badge.fury.io/rb/hyhyhy)

Pure & Professional presentations

## Introduction

It's a tool for easily creating pure and simple HTML5 presentations or websites.

Comes with a broad range of features: __Markdown, Nested slides, Math typesetting, Compatibility, Syntax highlighter, Javascript API, Convenient skeleton...__

#### More reading:

- [Installation](#installation): Step-by-step instructions for getting hyhyhy running on your computer.
- [Commands](#commands): List of commands.
- [Usage](#usage): Instructions stating how to use the framework.
- [Configuration](#configuration): Explanation of configure the tool.
- [Presentation](#presentation): Explanation of use the generated project.
- [Dependencies](#dependencies): List of used dependencies.
- [Quickstart](#quickstart): Step-by-step instructions for creating new project.
- [Example](#example): Preview in action.
- [Supported browsers](#supported-browsers): Explanation of browser support and fallbacks.
- [Contributing](#contributing): Explanation of how you can join the project.
- [License](#license): Clarification of certain rules.

## Installation

Binary installers for the latest released version are available at the [RubyGems.](https://rubygems.org/gems/hyhyhy)

```bash
$ gem install hyhyhy
```

You can create a new project by generating structure like this. Make sure that the destination folder does not exist because it will be overwritten.

```bash
hyhyhy
├── _assets
│   ├── javascripts
│   │   └── main.js
│   └── stylesheets
│       └── main.css
├── _includes
│   └── bower.json
├── _layouts
│   └── default.erb
├── _slides
│   ├── 1.introduction.md
│   ├── 2.packages.md
│   ├── ...
│   └── n.html
├── .bowerrc
├── .hyhyhy
└── README.md
```

## Commands

### New

Creates a default structure.

```bash
$ hyhyhy new
```

<div align="center">
  <img src="https://dl.dropboxusercontent.com/u/103345209/Screenshots/Screenshot%202014-12-14%2022.07.43.png"/>
</div>

### Build

This function should splice all your slides/sections in one presentation.
When you build your project it will generate a static version in the build folder that you can use.

```bash
$ hyhyhy build
```

<div align="center">
  <img src="https://dl.dropboxusercontent.com/u/103345209/Screenshots/Screenshot%202014-12-14%2022.10.20.png"/>
</div>

### Serve

Serve your presentation locally.

```bash
$ hyhyhy serve
```

<div align="center">
  <img src="https://dl.dropboxusercontent.com/u/103345209/Screenshots/Screenshot%202014-12-14%2022.10.56.png"/>
</div>

### Help

Displays a brief summary of the basic functions.

```bash
$ hyhyhy --help
```

### Version

Displays a version.

```bash
$ hyhyhy --version
```

## Usage

NOT READY, YET.

## Configuration

For now, you can change the basic variables in the configuration file.

```json
{
  "title": "hyhyhy",
  "description": "Pure & Professional presentations",
  "author": "Maciej A. Czyzewski"
}
```

## Presentation

- Press `left arrow` and `right arrow` to navigate.
- Press `h` to launch fullscreen.
- Press `ESC` to exit fullscreen mode.
- Browser zooming is supported.
- Touch events are supported.

## Dependencies

- Ruby (>= 2.0.0)
    * commander
    * kramdown
    * launchy
    * listen
    * erubis
    * bundler
    * rake
- Javascript
    * prism.js
    * MetricsGraphics.js
    * katex.js

## Quickstart

```bash
$ gem install hyhyhy
$ hyhyhy new
$ cd new_empty_presentation
$ hyhyhy build --watch --serve
```

## Example

Sample presentation is already in the project. But if you want you can see it live [by clicking this link.](http://maciejczyzewski.me/hyhyhy)

## Supported browsers

- Firefox 2+
- Safari 3+
- Opera 9.64+
- Chrome
- IE9, IE10, IE11

## Conceptions

- [ ] speaker notes

## Contributing

Please feel free to contribute to this project! Pull requests and feature requests welcome! :v:

## License

See LICENSE file in this repository.

## Thanks

* Kim Thoenen ([@Chive](https://github.com/Chive))