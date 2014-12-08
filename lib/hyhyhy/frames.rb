module Hyhyhy
  module Frames
    extend self

    @slides = []

    def all
      @slides
    end

    def explore(source)
      files = Dir.entries(source + '/_slides/').select { |f| !File.directory? f }

      files.each do |filename|
        content = File.read(source + '/_slides/' + filename)

        slides = []
        header = []

        content.split('---').each do |content|
          group = []
          content = content.strip

          content.split("\n").each do |option|
            option = option.split(": ", 2)

            if option[0] == nil || option[1] == nil
              group = []
              break
            else
              group.push({
                :name => option[0],
                :value => option[1]
              })
            end
          end

          if group == [] && content != ""
            case File.extname(filename)
            when '.md'
              content = Kramdown::Document.new(content, :input => 'GFM')
            else
              content = Kramdown::Document.new(content)
            end

            slides.push({
              :header => header,
              :document => content.to_html.strip
            })
          else
            header = group
          end
        end

        @slides += slides
      end
    end

    def implode(source, config)
      locals = {
        title: config['title'],
        description: config['description'],
        author: config['author']
      }

      locals['slides'] = @slides

      locals['slides'].map { |slide|
        slide[:header] = Parser.header(slide[:header])
      }

      template = File.open(source + '/_layouts/default.erb', "rb").read

      return Erubis::Eruby.new(template).result(locals)
    end

    def save(source, destination, config)
      @slides = []

      Config.load(source + '/.hyhyhy')

      Frames.explore(source)

      FileUtils.copy_entry source + '/_assets', destination

      File.write(
        destination + '/index.html',
        Frames.implode(source, config)
      )
    end
  end
end