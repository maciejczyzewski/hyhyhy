# encoding: utf-8

module Hyhyhy
  module Logger
    extend self

    @types = {
      :input  => "  >> ",
      :output => "# => ",
      :echo   => "#    ",
      :nil    => ""
    }

    @buffer = []

    def all
      @buffer
    end

    def spit(line, type = :nil)
      if line[0] == ','
        all[all.length - 1] += ','
        line = line[2..line.length]
      end

      all.push(@types[type] + line)
    end

    def hear(name)
      return ask(@types[:input] + name)
    end

    def ahoy()
      puts all.join("\n")
      Logger.clear
    end

    def clear()
      all = []
    end
  end
end