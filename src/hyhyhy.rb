# encoding: utf-8

require 'commander'
require 'kramdown'
require 'listen'

# Set encoding (UTF_8), globally
Encoding.default_internal = Encoding::UTF_8
Encoding.default_external = Encoding::UTF_8

module Hyhyhy
  autoload :Version, "hyhyhy/version"

  #autoload :Frames, "hyhyhy/frames"
  #autoload :Config, "hyhyhy/config"
  #autoload :Logger, "hyhyhy/logger"
  #autoload :Parser, "hyhyhy/parser"

  def self.initialize
    trap('INT') { Process.exit!(true) }
  end

  require "hyhyhy/command"
end

# build
# new
# serve
# list