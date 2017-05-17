require_relative '../abstract_linter'
require_relative 'json_converter'

module Coala
  class PythonLinter < ::AbstractLinter
    def results
      json_coala = `coala -I --files #{@file_absolute_path} --bears PyLintBear --json`
      Coala::JsonConverter.convert_json_from_coala_to_codemirror(json_coala)
    end

    def extension
      ".py"
    end
  end
end
