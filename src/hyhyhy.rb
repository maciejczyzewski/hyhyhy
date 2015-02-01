# encoding: utf-8

###############################################################################
#                                       _           _           _             #
#  Project                             | |         | |         | |            #
#                                      | |__  _   _| |__  _   _| |__  _   _   #
#  Copyright (C) 2005 - 2015,          | '_ \| | | | '_ \| | | | '_ \| | | |  #
#  Maciej A. Czyzewski,                | | | | |_| | | | | |_| | | | | |_| |  #
#  <maciejanthonyczyzewski@gmail.com>  |_| |_|\__, |_| |_|\__, |_| |_|\__, |  #
#                                              __/ |       __/ |       __/ |  #
#                                             |___/       |___/       |___/   #
#                                                                             #
#  This software is licensed as described in the file LICENSE, which          #
#  you should have received as part of this distribution.                     #
#                                                                             #
###############################################################################

# Libraries used in the project
require "commander"
require "maruku"
require "listen"

# Repair relative paths
$LOAD_PATH.unshift File.dirname(__FILE__)

# Set encoding (UTF_8), globally
Encoding.default_internal = Encoding::UTF_8
Encoding.default_external = Encoding::UTF_8

# =============================================================================
# MAIN MODULE
# =============================================================================

#
#     title: My cat, future, present!     |  Instead of giving settings at the
#     author: Maciej A. Czyzewski         |  beginning of the file, you can
#     animate: fadeIn                     |  save it in the .hyhyhy file
#     ---                                 |
#                                         |  Presentations can be written
#     # My cat, future, present!          |  in Markdown, but also in HTML5.
#                                         |
#     I like my __cat__!                  |  Wrap TeX in $ or $$ delimiters.
#                                         |  Slides are separated by a dash.
#     $$ a^2 + b^2 = c^2 $$               |  > ---
#                                         |
#     ---                                 |  The transitions between slides
#                                         |  can be defined, just by specify
#     - *Happy*                           |  the name.
#     - **Happy**                         |  > daneden.github.io/animate.css
#     - ~~Happy~~                         |
#                                         |  Of course we can put inside
#     ---                                 |  some pieces of code. It use
#                                         |  syntax highlighter called Rainbow.
#     ```bash                             |
#     rm -rf *.cats                       |  ╔═════════════════════════════╗
#     ```                                 |  ║ .out ┌───────────────┐      ║
#                                         |  ║      │ .in           │      ║
#     ---                                 |  ║      │               │      ║
#                                         |  ║      │               │      ║
#     <b>M. A. Czyzewski</b>              |  ║      └───────────────┘      ║
#     Thx!                                |  ╚═════════════════════════════╝
#

module Hyhyhy
  autoload :Frames, "hyhyhy/frames"
  # autoload :Config, "hyhyhy/config"
  # autoload :Logger, "hyhyhy/logger"
  autoload :Parser, "hyhyhy/parser"

  # The current version
  VERSION = "0.0.2"

  # Basic informations
  SUMMARY = %q{Pure & Professional presentations}
  DESCRIPTION = %q{A tool for creating nice looking HTML5 presentations.}

  # Someone has to be at the forefront
  AUTHOR = %q{M. A. Czyzewski <maciejanthonyczyzewski@gmail.com>}

  def self.initialize
    trap('INT') { Process.exit!(true) }

    require 'rubygems'
    require 'commander/import'

    program :name, 'hyhyhy'
    program :version, Hyhyhy::VERSION
    program :description, Hyhyhy::DESCRIPTION
    program :help, 'Author', Hyhyhy::AUTHOR

    Dir[File.dirname(__FILE__) + "/hyhyhy/commands/*.rb"].each {
      |file| require file
    }
  end
end

# =============================================================================
# COMMAND LINE INTERFACE
# =============================================================================

Hyhyhy.initialize