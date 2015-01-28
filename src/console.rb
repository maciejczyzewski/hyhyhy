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

