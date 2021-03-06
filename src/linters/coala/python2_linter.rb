require_relative "python_linter"

module Coala
  class Python2Linter < PythonLinter
    def results
        json_coala = `coala -I --files #{@file_absolute_path} --bears PyLintBear2 --json`
        Coala::JsonConverter.convert_json_from_coala_to_codemirror(json_coala)
    end
  end
end
