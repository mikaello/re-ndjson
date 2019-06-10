let nextLine = ndjsonChannel => {
  switch (Pervasives.input_line(ndjsonChannel)) {
  | line =>
    Some(
      switch (Yojson.Basic.from_string(line)) {
      | exception (Yojson.Json_error(msg)) =>
        Yojson.Basic.from_string(
          Printf.sprintf({|{error: "%s"}|}, "failed parsing"),
        )
      | validJson => validJson
      },
    )
  | exception End_of_file => None
  };
};

let buildJson = (initLine, channel) => {
  let rec buildJson' = (jsonList: list(Yojson.Basic.t)) => {
    switch (nextLine(channel)) {
    | Some(line) => List.cons(line, buildJson'(jsonList))
    | None => jsonList
    };
  };

  buildJson'([initLine]);
};

let toJsonArrayFromList = listOfJson => {
  let listAsString =
    listOfJson |> List.map(Yojson.Basic.to_string) |> String.concat(", ");

  Yojson.Basic.from_string("[" ++ listAsString ++ "]");
};

let ndjsonToJson = (~firstLine=None, ndjsonChannel) => {
  let json =
    switch (firstLine) {
    | Some(line) => buildJson(line, ndjsonChannel)
    | None =>
      switch (nextLine(ndjsonChannel)) {
      | Some(line) => buildJson(line, ndjsonChannel)
      | None => [Yojson.Basic.from_string("{}")]
      }
    };

  Pervasives.close_in(ndjsonChannel);
  json |> toJsonArrayFromList |> Yojson.Basic.pretty_to_string;
};