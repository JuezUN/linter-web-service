require 'sinatra'
require_relative 'linters/coala/java_linter'
require_relative 'linters/coala/python_linter'
require_relative 'linters/cpp_linter'

before do
  cross_origin
end

post '/cpp' do
  Oclint::CppLinter.new(params["code"]).perform_lint
end

post "/java" do
  Coala::JavaLinter.new(params["code"]).perform_lint
end

post '/python' do
  Coala::PythonLinter.new(params["code"]).perform_lint
end

#The remaining not-matched paths will end here
post '/*' do
  missing_language = missing_language_from_url(request.url)
  "The linter for the language #{missing_language} is not installed. Please, contact the system administrator"
end

def cross_origin
  headers 'Access-Control-Allow-Origin' => '*'
end

def missing_language_from_url(url)
  url.split('/').last
end
