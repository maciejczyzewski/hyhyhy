# encoding: utf-8
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
  spec.homepage      = "https://github.com/maciejczyzewski/hyhyhy"
  spec.license       = "MIT"

  spec.files         = `git ls-files -z`.split("\x0")
  spec.executables   = spec.files.grep(%r{^bin/}) { |f| File.basename(f) }
  spec.test_files    = spec.files.grep(%r{^(test|spec|features)/})
  spec.require_paths = ["lib"]

  spec.add_runtime_dependency "commander", "~> 4.0", ">= 4.0.0"
  spec.add_runtime_dependency "kramdown", "~> 1.4", ">= 1.4.0"
  spec.add_runtime_dependency "launchy", "~> 2.3", ">= 2.3.0"
  spec.add_runtime_dependency "listen", "~> 2.7", ">= 2.7.0"
  spec.add_runtime_dependency "erubis", "~> 2.6", ">= 2.6.0"

  spec.add_development_dependency "bundler", "~> 1.7"
  spec.add_development_dependency "rake", "~> 10.0"

  spec.required_ruby_version = '>= 1.9.3'
end
