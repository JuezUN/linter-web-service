require_relative "../abstract_linter"
require_relative 'json_converter'

module Coala
  class JavaLinter < ::AbstractLinter
    def results
      json_coala = `coala -I --files #{@file_absolute_path} --bears JavaPMDBear --json`
      Coala::JsonConverter.convert_json_from_coala_to_codemirror(json_coala)
    end

    def extention
      ".java"
    end
  end
end
