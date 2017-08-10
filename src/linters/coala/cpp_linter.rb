require_relative "oclinter"

module Coala
  class CppLinter < OcLinter
    def extension
      ".cpp"
    end
  end
end
