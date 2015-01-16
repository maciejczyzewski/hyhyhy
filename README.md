<div align="center">
  <img src="https://dl.dropboxusercontent.com/u/103345209/Screenshots/Screenshot%202014-12-14%2021.40.38.png"/>
</div>

# hyhyhy [![Gem Version](https://badge.fury.io/rb/hyhyhy.svg)](http://badge.fury.io/rb/hyhyhy)

> _A Ruby library for creating and outputting professional, business-looking (HTML5) presentations that can be viewed inside the browser!_

## Introduction

__hyhyhy__ is used from the _Ruby CLI_ and relies on a series of steps that developers (and even regular users) can go through to build a simple presentation.

Once these steps completed, an HTML5 file is generated which can be accessed, viewed, and hosted online.

## Features

All hyhyhy presentations come with support for a wide range of features, like __Markdown text formatting__, __page transitions__, __sequential transitions__ for objects on the page, __syntax highlighting__, and __mathematical functions__.

There’s also support for __keyboard shortcuts__, showing the position inside the overall __presentation timeline__, __hashed URLs__ for easy deep-linking, __automatic rebuilds__ on content changes, __responsive layouts__, and __touch gestures__ on mobile devices.

All presentations are very well supported across browsers and the library also includes lots of documentation.

#### More reading:

- [Installation](#installation): Step-by-step instructions for getting hyhyhy running on your computer.
- [Quickstart](#quickstart): Step-by-step instructions for creating new project.
- [Commands](#commands): List of Ruby CLI commands.
- [Usage](#usage): Instructions stating how to use the framework.
- [Configuration](#configuration): Explanation of configure the tool.
- [Dependencies](#dependencies): List of used dependencies in the project.
- [Supported browsers](#supported-browsers): Explanation of browser support and fallbacks.
- [Presentation](#presentation): Explanation of use the generated project.
- [Example](#example): Sample available immediately after installation.
- [Contributing](#contributing): Explanation of how you can join the project.
- [Conceptions](#conceptions): List of ideas for the future.
- [License](#license): Clarification of certain rules.

## Installation

Binary installers for the latest released version are available at the [RubyGems.](https://rubygems.org/gems/hyhyhy)

```bash
$ gem install hyhyhy
```

You can create a new project by generating structure like this. Make sure that the destination folder does not exist because it will be overwritten.

```bash
my-new-presentation
├── _assets                # Assets, own catalogs
│   ├── javascripts        # Scripts
│   │   └── main.js        # Core (presentation)
│   └── stylesheets        # Styles
│       └── main.css       # Default
├── _includes              # Bower components
│   └── bower.json         # Package list
├── _layouts               # Layouts
│   └── default.erb        # Basic template
├── _slides                # Slides/Sections
│   ├── 1.introduction.md  # First group
│   ├── 2.packages.md      # Second group
│   ├── ...                # ...
│   └── n.html             # Last gruop
├── .bowerrc               # Bower configure
├── .hyhyhy                # Hyhyhy configure
└── README.md              # Simplified guide
```

## Quickstart

```bash
$ gem install hyhyhy
$ hyhyhy new
$ cd new_empty_presentation
$ hyhyhy build --watch --serve
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

NOT READY, YET! SEE MAIN PRESENTATION...

## Configuration

For now, you can change the basic variables in the `.hyhyhy` configuration file.

```json
{
  "title": "hyhyhy",
  "description": "Pure & Professional presentations",
  "author": "Maciej A. Czyzewski"
}
```

## Dependencies

- Ruby (>= 1.9.3)
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
- Others
    * bower (optional)

## Supported browsers

- Firefox 2+
- Safari 3+
- Opera 9.64+
- Chrome
- IE9, IE10, IE11

## Presentation

- Press (`space` or `shift + space`), (`left arrow` or `right arrow`) and (`k` or `j`) to navigate.
- Press `h` to launch fullscreen.
- Press `ESC` to exit fullscreen mode.
- Press `gg`/`shift + g` to move to top/bottom.
- Browser zooming is supported.
- Touch events are supported.

## Example

Sample available immediately after installation. You can see it live [by clicking this link.](http://maciejczyzewski.me/hyhyhy)

## Contributing

The goal was to make package that will speed up work on own presentation.Please feel free to contribute to this project! Pull requests and feature requests welcome! :v:

## Conceptions

- [ ] speaker notes
- [ ] travis tests
- [ ] compression

## License

See LICENSE file in this repository.

## Credits

<div align="center">
  <img src="http://bower.io/img/bower-logo.png" width="200px" />
  <img src="http://www.stockholmruby.com/logo.png" width="200px" />
  <img src="https://khan.github.io/KaTeX/katex-logo.svg" width="300px" />
  <img src="http://upload.wikimedia.org/wikipedia/commons/4/4b/O_Reilly_Media_logo.svg" width="200px" />
  <img src="http://metricsgraphicsjs.org/images/logo.svg" width="300px" />
  <img src="http://upload.wikimedia.org/wikipedia/commons/a/aa/Logo_Google_2013_Official.svg" width="200px" />
</div>

## Thanks

* Kim Thoenen ([@Chive](https://github.com/Chive))
* Anderson de Oliveira ([@andersonba](https://github.com/andersonba))
* Jorge Epuñan ([@juanbrujo](https://github.com/juanbrujo))