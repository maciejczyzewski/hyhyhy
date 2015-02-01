# encoding: utf-8

command :create do |c|
  c.syntax = 'hyhyhy create'
  c.description = 'Forms the skeleton of a new presentation.'
  c.action do |args, options|
    puts "CREATE"
  end
end