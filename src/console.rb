#!/usr/bin/env ruby
# encoding: utf-8

# Set encoding (UTF_8), globally
Encoding.default_internal = Encoding::UTF_8
Encoding.default_external = Encoding::UTF_8

puts "Hi! :-D"

# Function: bash output during process
def bash *args
  abort "Failed during: #{args.shell_s}" unless Kernel.system(*args)
end

# markdown --all-block --all-span --all-flags -all-negative

p ENV

# ---------------------------------------------------------------

require 'rubygems'
require 'commander/import'

# :name is optional, otherwise uses the basename of this executable
program :name, 'Foo Bar'
program :version, '1.0.0'
program :description, 'Stupid command that prints foo or bar.'

command :foo do |c|
  c.syntax = 'foobar foo'
  c.description = 'Displays foo'
  c.action do |args, options|
    say 'foo'
  end
end

command :bar do |c|
  c.syntax = 'foobar bar [options]'
  c.description = 'Display bar with optional prefix and suffix'
  c.option '--prefix STRING', String, 'Adds a prefix to bar'
  c.option '--suffix STRING', String, 'Adds a suffix to bar'
  c.action do |args, options|
    options.default :prefix => '(', :suffix => ')'
    say "#{options.prefix}bar#{options.suffix}"
  end
end