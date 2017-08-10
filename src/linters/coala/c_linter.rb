require_relative "oclinter"

module Coala
  class CLinter < OcLinter
    def extension
      ".c"
    end
  end
end