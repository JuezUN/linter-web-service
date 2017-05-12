require_relative 'abstract_linter'

module Oclint
  class CppLinter < AbstractLinter
    def results
      `oclint-0.12 -report-type json #{@file_absolute_path} -- -c -enable-clang-static-analyzer`
    end

    def extension
      ".cpp"
    end
  end
end
