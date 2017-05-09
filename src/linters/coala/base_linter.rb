require 'json'

module Coala
  class BaseLinter

    def initialize(file_absolute_path = "")
      @file_absolute_path = file_absolute_path
    end

    def convert_json_from_coala_to_codemirror(coala_json)
      coala_object = JSON.parse(coala_json)
      coala_errors = coala_object["results"]["default"]
      coala_errors.map{ |error| mirror_error_from_coala_error(error) }.to_json
    end

    def results
      []
    end

    private

    def mirror_error_from_coala_error(coala_error)
      code_mirror_error = {}
      code_mirror_error["severity"] = code_mirror_severity(coala_error)
      code_mirror_error["from"] = starting_position(coala_error)
      code_mirror_error["to"] = ending_position(coala_error)
      code_mirror_error["message"] = coala_error["message"]
      code_mirror_error
    end

    def code_mirror_severity(error)
      "warning"
    end

    def starting_position(error)
      from = {}
      start = error["affected_code"][0]["start"]
      from["line"] = start["line"] - 1
      from["ch"] = (start["column"] == nil ? 0 : start["column"] - 1)
      from["sticky"] = nil
      from
    end

    def ending_position(error)
      to = {}
      start = error["affected_code"][0]["start"]
      ending = error["affected_code"][0]["end"]

      whole_line_error = ending["column"] == nil && start["column"] == nil

      if whole_line_error
        to["line"] = ending["line"]
        to["ch"] = 0
      else
        to["line"] = ending["line"] - 1
        to["ch"] = (ending["column"] == nil ? 0 : ending["column"] - 1)
      end

      to["sticky"] = nil
      to
    end
  end

end
