open TestFramework;

describe("ndjson utils", ({test}) => {
  test("that toJsonArrayFromList works as expected", ({expect}) => {
    let listOfJson = [
      Yojson.Basic.from_string("{a: true}"),
      Yojson.Basic.from_string("{b: \"hello\"}"),
    ];
    let jsonConverted =
      ReNdjson.NdjsonUtil.toJsonArrayFromList(listOfJson)
      |> Yojson.Basic.to_string;

    expect.string(jsonConverted).toEqual({j|[{"a":true},{"b":"hello"}]|j});
  });

  test("that toJsonArrayFromList works for empty objects", ({expect}) => {
    let listOfEmptyObject = [Yojson.Basic.from_string("{}")];
    let jsonConverted =
      ReNdjson.NdjsonUtil.toJsonArrayFromList(listOfEmptyObject)
      |> Yojson.Basic.to_string;

    expect.string(jsonConverted).toEqual({j|[{}]|j});
  });
});

// Start tests
cli();