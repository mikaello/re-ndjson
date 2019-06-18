type convertMethod =
  | NdjsonToJson(string)
  | JsonToNdjson(string)
  | Unknown(string);

let convertNdjsonToJson = inputFile => {
  let file = Pervasives.open_in(inputFile);
  NdjsonUtil.ndjsonToJson(file);
};

let convertJsonToNdjson = inputFile => {
  let json = Yojson.Basic.from_file(inputFile);

  let listOfObjects = Yojson.Basic.Util.to_list(json);

  listOfObjects |> List.map(Yojson.Basic.to_string) |> String.concat("\n");
};

let convertUnknown = inputFile => {
  let file = Pervasives.open_in(inputFile);

  let firstLine = Pervasives.input_line(file);

  switch (Yojson.Basic.from_string(firstLine)) {
  | exception (Yojson.Json_error(_msg)) =>
    Pervasives.close_in(file);
    convertJsonToNdjson(inputFile);
  | `Assoc(_) as ndjson => NdjsonUtil.ndjsonToJson(~firstLine=ndjson, file)
  | json =>
    Pervasives.close_in(file);
    convertJsonToNdjson(inputFile);
  };
};

let convertInput = method =>
  switch (method) {
  | NdjsonToJson(file) => convertNdjsonToJson(file)
  | JsonToNdjson(file) => convertJsonToNdjson(file)
  | Unknown(file) => convertUnknown(file)
  };