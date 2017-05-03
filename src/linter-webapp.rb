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
  "The language you are trying to lint is not installed. Contact the system administrator"
end
