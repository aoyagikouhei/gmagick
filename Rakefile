require "bundler/gem_helper"
gem_helper = Bundler::GemHelper.new(Dir.pwd)
gem_helper.install
gem_spec = gem_helper.gemspec

require 'rdoc/task'
RDoc::Task.new do |rdoc|
  rdoc.rdoc_files.include("lib/**/*.rb", "ext/gmagick/*.c")
end

require 'rake/clean'

require 'rake/testtask'
Rake::TestTask.new

require 'rake/extensiontask'
module Rake
  class BaseExtensionTask
    def binary(platform = nil)
      ext = case platform
        when /darwin/
          'bundle'
        when /mingw|mswin|linux/
          'so'
        when /java/
          'jar'
        else
          RbConfig::CONFIG['DLEXT']
      end
      "#{@name}n.#{ext}"
    end
  end
end

Rake::ExtensionTask.new(gem_spec.name, gem_spec)

require "rspec/core/rake_task"
RSpec::Core::RakeTask.new(:spec)