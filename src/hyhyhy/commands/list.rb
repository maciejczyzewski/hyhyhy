# encoding: utf-8

command :list do |c|
  c.syntax = 'hyhyhy list'
  c.description = 'Shows a list of presentations.'
  c.action do |args, options|
    puts "LIST"
  end
end