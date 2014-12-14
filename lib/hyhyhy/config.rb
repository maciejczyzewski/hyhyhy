require 'json'

module Hyhyhy
  module Config
    extend self

    @filename = './.hyhyhy'
    @settings = {}

    def load(filename)
      @filename = filename
      @settings = JSON.parse(File.read(@filename))
    end

    def all
      @settings
    end

    def [](key)
      all[key]
    end

    def []=(key, value)
      all[key] = value

      File.open(@filename, 'w') { |f| f.write(JSON.pretty_generate(@settings)) }
    end
  end
end