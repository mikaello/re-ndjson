let one = () => 1;

let print_results = strings => List.map(l => print_endline(l), strings);
let print_list = strings =>
  Printf.printf("Files: %s", String.concat(", ", strings));

let file_in_channel = Pervasives.open_in("./test.json");

let file = Pervasives.open_in("./test.ndjson");

let first_line = Pervasives.input_line(file);

let ndjsonToJson = (firstLine, ndjsonChannel) => {
  print_endline("ndjson_to_json");
  let nextLine = () => {
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

  let buildJson = initLine => {
    let rec buildJson' = (jsonList: list(Yojson.Basic.t)) => {
      switch (nextLine()) {
      | Some(line) => List.cons(line, buildJson'(jsonList))
      | None => jsonList
      };
    };

    buildJson'([initLine]);
  };

  let json = buildJson(firstLine);
  Pervasives.close_in(ndjsonChannel);
  json;
};

let toJsonArrayFromList = listOfJson => {
  let listAsString =
    listOfJson |> List.map(Yojson.Basic.to_string) |> String.concat(", ");

  Yojson.Basic.from_string("[" ++ listAsString ++ "]");
};

switch (Yojson.Basic.from_string(first_line)) {
| exception (Yojson.Json_error(msg)) => print_endline("probably json1")
| `Assoc(_) as ndjson =>
  ndjsonToJson(ndjson, file)
  |> toJsonArrayFromList
  |> Yojson.Basic.pretty_to_string
  |> print_endline
| json => print_endline("probably json2")
};

// file_stream |> Stream.iter(line => print_endline(line));

//let test = Core.In_channel.read_all("./test.json");

//let yo_test = Yojson.Basic.from_string(test);

/*
 switch (yo_test) {
 | `List(_l) => print_endline("is a list")
 | _ => print_endline("not a list")
 };

 switch (Yojson.Basic.from_file("./test.ndjson")) {
 | exception (Yojson.Json_error(msg)) => print_endline(msg)
 | _ => print_endline("valid")
 };
 */