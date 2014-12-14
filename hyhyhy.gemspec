# coding: utf-8
lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'hyhyhy/version'

Gem::Specification.new do |spec|
  spec.name          = "hyhyhy"
  spec.version       = Hyhyhy::VERSION
  spec.authors       = ["Maciej A. Czyzewski"]
  spec.email         = ["maciejanthonyczyzewski@gmail.com"]
  spec.summary       = Hyhyhy::SUMMARY
  spec.description   = Hyhyhy::DESCRIPTION
  spec.homepage      = "https://github.com/MaciejCzyzewski/hyhyhy"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_runtime_dependency "commander", "~> 4.1", ">= 4.1.0"
  spec.add_runtime_dependency "kramdown", "~> 1.5", ">= 1.5.0"
  spec.add_runtime_dependency "launchy", "~> 2.4", ">= 2.4.3"
  spec.add_runtime_dependency "listen", "~> 2.8", ">= 2.8.0"
  spec.add_runtime_dependency "erubis", "~> 2.7", ">= 2.7.0"

  spec.add_development_dependency "bundler", "~> 1.7"
  spec.add_development_dependency "rake", "~> 10.0"
end
