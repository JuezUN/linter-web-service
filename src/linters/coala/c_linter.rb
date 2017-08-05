require_relative "cpp_linter"

module Coala
  class CLinter < CppLinter
    def extension
      ".c"
    end
  end
end