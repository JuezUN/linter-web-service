require 'sinatra'
require_relative 'linters/coala/java_linter'
require_relative 'linters/coala/python_linter'
require_relative 'linters/cpp_linter'

post '/cpp' do
  cross_origin
  Oclint::CppLinter.new(params["code"]).perform_lint
end

post "/java" do
  cross_origin
  Coala::JavaLinter.new(params["code"]).perform_lint
end

post '/python' do
  cross_origin
  Coala::PythonLinter.new(params["code"]).perform_lint
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

def missing_language_from_url(url)
  url.split('/').last
end
