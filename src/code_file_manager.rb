require 'tempfile'

module CodeFileManager
  def next_file_absolute_path(extension)
    tempfile = Tempfile.create(['foo', extension], "#{Dir.pwd}/codes")
    tempfile.path
  end

  def write_code_to_file(file_absolute_path, code)
    File.open(file_absolute_path, "w") do |f|
      f.write code
    end
  end

  def erase_file(file_absolute_path)
    File.delete(file_absolute_path)
  end
end
