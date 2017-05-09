require_relative "base_linter"

module Coala
  class JavaLinter < BaseLinter
    def results
      json_coala = `coala -I --files #{@file_absolute_path} --bears JavaPMDBear --json`
      convert_json_from_coala_to_codemirror(json_coala)
    end
  end
end
