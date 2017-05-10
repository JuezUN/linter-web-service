require_relative 'abstract_linter'

module Oclint
  class CppLinter < AbstractLinter
    def results
      `/home/mauricio/linters/hw/bin/oclint-0.12 -report-type html #{@file_absolute_path} -- -c -enable-clang-static-analyzer`
    end

    def extention
      ".cpp"
    end
  end
end
