module Hyhyhy
  module Parser
    extend self

    def header(headers)
      return headers.map{|a| "#{a[:name]}='#{a[:value]}'"}.join(' ')
    end
  end
end