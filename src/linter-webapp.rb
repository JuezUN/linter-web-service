require 'sinatra'

post '/cpp' do
  code = params["code"]

  file_absolute_path = '/home/mauricio/linter-web/codes/code.cpp'
  File.open(file_absolute_path, "w") do |f|
    f.write code
  end

  `/home/mauricio/linters/hw/bin/oclint-0.12 -report-type html #{file_absolute_path} -- -c -enable-clang-static-analyzer`
end

post '/*' do
  missing_language = missing_language_from_url(request.url)
  "The linter for the language #{missing_language} is not installed. Please, contact the system administrator"
end

def missing_language_from_url(url)
  url.split('/').last
end
