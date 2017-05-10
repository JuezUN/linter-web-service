module CodeFileManager
  def next_file_absolute_path
    possible_letters = [('a'..'z'), ('A'..'Z')].map(&:to_a).flatten
    random_string = (0..10).map { possible_letters[rand(possible_letters.size)] }.join
    "#{Dir.pwd}/codes/#{random_string}"
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
