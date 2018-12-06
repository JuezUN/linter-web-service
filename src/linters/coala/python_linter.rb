require_relative '../abstract_linter'
require_relative 'json_converter'

module Coala
  class PythonLinter < ::AbstractLinter
    def extension
      ".py"
    end
  end
end
