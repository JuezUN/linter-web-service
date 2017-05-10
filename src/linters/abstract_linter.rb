require_relative '../code_file_manager'

class AbstractLinter
  include(CodeFileManager)

  def initialize(code="")
    @file_absolute_path = next_file_absolute_path + extention
    @code = code
  end

  def perform_lint
    write_code_to_file(@file_absolute_path, @code)
    response = results
    erase_file(@file_absolute_path)
    response
  end

  def results
    []
  end

  def extention
    ".txt"
  end
end
