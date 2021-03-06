require 'json'

#Codemirror json example:
# [
#   {
#     "severity": "warning",
#     "from": {
#       "line": 0,
#       "ch": 0,
#       "sticky": null
#     },
#     "to": {
#       "line": 1,
#       "ch": 0,
#       "sticky": null
#     },
#     "message": "Package name contains upper case characters"
#   },
#   {
#     "severity": "warning",
#     "from": {
#       "line": 5,
#       "ch": 0,
#       "sticky": null
#     },
#     "to": {
#       "line": 6,
#       "ch": 0,
#       "sticky": null
#     },
#     "message": "Avoid unused imports such as 'java.util.Scanner'"
#   }
# ]

module Coala
  class JsonConverter
    def self.convert_json_from_coala_to_codemirror(coala_json)
      coala_object = JSON.parse(coala_json)
      coala_errors = coala_object["results"]["cli"]
      coala_errors.map{ |error| mirror_error_from_coala_error(error) }.to_json
    end

    private

    def self.mirror_error_from_coala_error(coala_error)
      code_mirror_error = {}
      code_mirror_error["severity"] = severity(coala_error)
      code_mirror_error["from"] = starting_position(coala_error)
      code_mirror_error["to"] = ending_position(coala_error)
      code_mirror_error["message"] = coala_error["message"]
      code_mirror_error
    end

    def self.severity(error)
      return "error" if error["severity"] >= 2
      "warning"
    end

    def self.starting_position(error)
      from = {}
      start = error["affected_code"][0]["start"]
      from["line"] = start["line"] - 1
      from["ch"] = column_from_position(start)
      from["sticky"] = nil
      from
    end

    def self.ending_position(error)
      to = {}
      ending = error["affected_code"][0]["end"]

      if whole_line_error(error)
        to["line"] = ending["line"]
        to["ch"] = 0
      else
        to["line"] = ending["line"] - 1
        to["ch"] = column_from_position(ending)
      end

      to["sticky"] = nil
      to
    end

    def self.whole_line_error(error)
      start = error["affected_code"][0]["start"]
      ending = error["affected_code"][0]["end"]
      ending["column"] == nil && start["column"] == nil
    end

    def self.column_from_position(position)
      return 0 unless position
      return 0 if position["column"] == nil || position["column"] <= 0
      position["column"] - 1
    end
  end
end
