require_relative '../code_file_manager'

class AbstractLinter
  include(CodeFileManager)

  def initialize(code="")
    @code = code
  end

  def perform_lint
    begin
      @file_absolute_path = next_file_absolute_path(extension)
      write_code_to_file(@file_absolute_path, @code)
      response = results
    ensure
      erase_file(@file_absolute_path)
    end
    response
  end

  def results
    []
  end

  def extension
    ".txt"
  end
end
