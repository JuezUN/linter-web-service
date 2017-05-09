require_relative "../../spec_helper"

describe Coala do

  before do
    @base_linter = Coala::BaseLinter.new
    @coala_json = File.read('spec/linters/coala/coala_json.json')
  end

  it "gets the correct number of errors and warnings" do
    code_mirror_json = @base_linter.convert_json_from_coala_to_codemirror(@coala_json)
    code_mirror_errors = JSON.parse(code_mirror_json)
    expect(code_mirror_errors.size).to eq 24
  end

  it "gets the correct messages" do
    code_mirror_json = @base_linter.convert_json_from_coala_to_codemirror(@coala_json)
    code_mirror_errors = JSON.parse(code_mirror_json)
    expect(code_mirror_errors[0]["message"]).to eq "Package name contains upper case characters"
    expect(code_mirror_errors[1]["message"]).to eq "Avoid unused imports such as 'java.util.Scanner'"
  end

  it "gets the correct severities" do
    code_mirror_json = @base_linter.convert_json_from_coala_to_codemirror(@coala_json)
    code_mirror_errors = JSON.parse(code_mirror_json)
    expect(code_mirror_errors[0]["severity"]).to eq "warning"
    expect(code_mirror_errors[21]["severity"]).to eq "warning"
  end

  it "gets the correct starting error position" do
    code_mirror_json = @base_linter.convert_json_from_coala_to_codemirror(@coala_json)
    code_mirror_errors = JSON.parse(code_mirror_json)

    expect(code_mirror_errors[0]["from"]).to eq ({"line" => 0, "ch" => 0, "sticky" => nil})
    expect(code_mirror_errors[12]["from"]).to eq ({"line" => 89, "ch" => 0, "sticky" => nil})
    expect(code_mirror_errors[17]["from"]).to eq ({"line" => 124, "ch" => 0, "sticky" => nil})
    expect(code_mirror_errors[23]["from"]).to eq ({"line" => 201, "ch" => 1, "sticky" => nil})
  end


  it "gets the correct ending error position" do
    code_mirror_json = @base_linter.convert_json_from_coala_to_codemirror(@coala_json)
    code_mirror_errors = JSON.parse(code_mirror_json)

    expect(code_mirror_errors[0]["to"]).to eq ({"line" => 1, "ch" => 0, "sticky" => nil})
    expect(code_mirror_errors[12]["to"]).to eq ({"line" => 90, "ch" => 0, "sticky" => nil})
    expect(code_mirror_errors[17]["to"]).to eq ({"line" => 125, "ch" => 0, "sticky" => nil})
    expect(code_mirror_errors[23]["to"]).to eq ({"line" => 201, "ch" => 23, "sticky" => nil})
  end

  context "with not null columns" do
    before do
      @coala_json = File.read("spec/linters/coala/not_null_columns.json")
    end

    it "columns are never negative" do
      code_mirror_json = @base_linter.convert_json_from_coala_to_codemirror(@coala_json)
      code_mirror_errors = JSON.parse(code_mirror_json)

      not_negative = code_mirror_errors.all? do |error|
        error["from"]["ch"] >= 0 && error["to"]["ch"] >= 0
      end
      expect(not_negative).to eq (true)
    end
  end
end
