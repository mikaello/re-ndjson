type convertMethod =
  | NdjsonToJson
  | JsonToNdjson
  | Unknown;

let convertNdjsonToJson = input => {
  NdjsonUtil.ndjsonToJson(input);
};

let read_in_channel = (~startValue=?, input) => {
  let rec read_in_channel' = stringified_input => {
    switch (Pervasives.input_line(input)) {
    | line => read_in_channel'(stringified_input ++ line)
    | exception End_of_file => stringified_input
    };
  };

  switch (startValue) {
  | Some(value) => read_in_channel'(value)
  | None => read_in_channel'("")
  };
};

let convertJsonToNdjson = (~firstLineJson=?, ~firstLine=?, input) => {
  let json =
    switch (firstLine) {
    | Some(firstLine) =>
      input
      |> read_in_channel(~startValue=firstLine)
      |> Yojson.Basic.from_string
    | None =>
      switch (firstLineJson) {
      | Some(json) => json
      | None => Yojson.Basic.from_channel(input)
      }
    };

  let listOfObjects = Yojson.Basic.Util.to_list(json);

  listOfObjects |> List.map(Yojson.Basic.to_string) |> String.concat("\n");
};

let convertUnknown = input => {
  let firstLine = Pervasives.input_line(input);

  switch (Yojson.Basic.from_string(firstLine)) {
  | exception (Yojson.Json_error(_msg)) =>
    convertJsonToNdjson(~firstLine, input)
  | `Assoc(_) as ndjson => NdjsonUtil.ndjsonToJson(~firstLine=ndjson, input)
  | json => convertJsonToNdjson(~firstLineJson=json, input)
  };
};

let convertInput = (inputType, file) => {
  let input =
    if (file == "-") {
      Pervasives.stdin;
    } else {
      Pervasives.open_in(file);
    };

  let convertedInput =
    switch (inputType) {
    | NdjsonToJson => convertNdjsonToJson(input)
    | JsonToNdjson => convertJsonToNdjson(input)
    | Unknown => convertUnknown(input)
    };

  if (file != "-") {
    Pervasives.close_in(input);
  };

  convertedInput;
};