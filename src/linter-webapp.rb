require 'sinatra'
require_relative 'linters/coala/java_linter'
require_relative 'linters/coala/python_linter'

post '/cpp' do
  cross_origin
  code = params["code"]
  file_absolute_path = next_file_absolute_path + ".cpp"
  write_code_to_file(file_absolute_path, code)
  response = `/home/mauricio/linters/hw/bin/oclint-0.12 -report-type html #{file_absolute_path} -- -c -enable-clang-static-analyzer`
  erase_file(file_absolute_path)
  response
end

post "/java" do
  cross_origin
  code = params["code"]
  file_absolute_path = next_file_absolute_path + ".java"
  write_code_to_file(file_absolute_path, code)
  response = Coala::JavaLinter.new(file_absolute_path).results
  erase_file(file_absolute_path)
  response
end

post '/python' do
  cross_origin
  code = params["code"]
  file_absolute_path = next_file_absolute_path + ".py"
  write_code_to_file(file_absolute_path, code)
  response = Coala::PythonLinter.new(file_absolute_path).results
  erase_file(file_absolute_path)
  response
end

#The remaining not-matched paths will end here
post '/*' do
  cross_origin
  missing_language = missing_language_from_url(request.url)
  "The linter for the language #{missing_language} is not installed. Please, contact the system administrator"
end

def cross_origin
  headers 'Access-Control-Allow-Origin' => '*'
end

def next_file_absolute_path
  possible_letters = [('a'..'z'), ('A'..'Z')].map(&:to_a).flatten
  random_string = (0..10).map { possible_letters[rand(possible_letters.size)] }.join
  "/home/mauricio/linter-web/codes/#{random_string}"
end

def write_code_to_file(file_absolute_path, code)
  File.open(file_absolute_path, "w") do |f|
    f.write code
  end
end

def erase_file(file_absolute_path)
  File.delete(file_absolute_path)
end

def missing_language_from_url(url)
  url.split('/').last
end
