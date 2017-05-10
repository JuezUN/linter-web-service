require_relative 'base_linter'

module Coala
  class PythonLinter < BaseLinter
    def results
      json_coala = `coala -I --files #{@file_absolute_path} --bears PyLintBear --json`
      convert_json_from_coala_to_codemirror(json_coala)
    end

    def extention
      ".py"
    end
  end
end
