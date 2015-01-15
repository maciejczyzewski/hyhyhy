require 'listen'
require 'erubis'
require 'launchy'
require 'webrick'
require 'kramdown'

Encoding.default_internal = Encoding::UTF_8
Encoding.default_external = Encoding::UTF_8

module Hyhyhy
  autoload :Version, "hyhyhy/version"

  autoload :Frames, "hyhyhy/frames"
  autoload :Config, "hyhyhy/config"
  autoload :Logger, "hyhyhy/logger"
  autoload :Parser, "hyhyhy/parser"

  def self.initialize
    trap('INT') { Process.exit!(true) }
  end

  def self.new(args, options)
    if options.title == nil
      options.title = Logger.hear("Title: ")
    end

    if options.description == nil
      options.description = Logger.hear("Description: ")
    end

    if options.author == nil
      options.author = Logger.hear("Author: ")
    end

    if args[0] == nil
      args[0] = './' + options.title.downcase.strip.gsub(' ', '-').gsub(/[^\w-]/, '')
    end

    FileUtils.copy_entry File.dirname(__FILE__) + '/hyhyhy/structure', args[0]

    Config.load(args[0] + '/.hyhyhy')

    Config['title'] = options.title
    Config['description'] = options.description
    Config['author'] = options.author

    # Informing about the success!
    Logger.spit("Default structure will be generated into " + args[0], :output)
    Logger.ahoy()
  end

  def self.build(args, options)
    if options.source == './' && options.destination == './_build'
      Logger.spit("The current folder will be generated into ./_build", :output)
    elsif options.source == './' && options.destination != './_build'
      Logger.spit("The current folder will be generated into " + options.destination, :output)
    else options.source != './'
      Logger.spit("The " + options.source + " folder will be generated into " + options.destination, :output)
    end

    if options.watch == true
      Logger.spit(", watched for changes, and regenerated automatically.", :echo)
    end

    Logger.ahoy() # To inform you about what we do...

    Frames.save(options.source, options.destination)

    if options.serve == true
      Thread.new() do
        self.serve(args, options)
      end
    end

    if options.watch == true
      listener = Listen.to(options.source, :ignore => /_build/) do |modified, added, removed|
        Logger.spit("Regeneration.... #{modified} #{added} #{removed}", :output)
        Logger.ahoy()

        Frames.save(options.source, options.destination)
      end
      listener.start
      sleep
    end
  end

  def self.serve(args, options)
    if args[0] == nil || args[0] = '.'
      args[0] = './_build'
    end

    if options.open == true
      Launchy.open(args[0] + '/index.html')
    end

    Logger.spit("Now browse to http://localhost:4000", :output)
    Logger.ahoy()

    server = WEBrick::HTTPServer.new :Port => 4000
    server.mount "/", WEBrick::HTTPServlet::FileHandler, args[0]
    trap('INT') { server.stop; Process.exit!(true) }
    server.start
  end
end