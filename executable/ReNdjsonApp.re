open Cmdliner;
let version = "1.0.0";

type flagType =
  | Json
  | Ndjson
  | Unspecified;

let unknownFileType = (flagType, file) =>
  (
    switch (flagType) {
    | Unspecified => ReNdjson.Util.convertInput(Unknown(file))
    | Json => ReNdjson.Util.convertInput(JsonToNdjson(file))
    | Ndjson => ReNdjson.Util.convertInput(NdjsonToJson(file))
    }
  )
  |> print_endline;

/** Custom converter to accept '-' as valid filename (for stdin) */
let stdin_or_non_dir_file = {
  let (parse as arg_parse, pp_print) = Arg.non_dir_file;

  let parse = s =>
    if (s == "-") {
      `Ok(s);
    } else {
      arg_parse(s);
    };

  (parse, pp_print);
};

let file =
  Arg.(
    required
    & pos(0, some(stdin_or_non_dir_file), None)
    & info([], ~docv="FILE")
  );

let convertFlag = {
  let doc = "Convert from JSON file";
  let jsonFlag = (Json, Arg.info(["j", "from-json"], ~doc));

  let doc = "Convert from NDJSON file";
  let ndjsonFlag = (Ndjson, Arg.info(["n", "from-ndjson"], ~doc));

  Arg.(last & vflag_all([Unspecified], [jsonFlag, ndjsonFlag]));
};

let cmd = {
  let doc = "convert to/from NDJSON to/from JSON";
  let man = [
    `S(Manpage.s_description),
    `P(
      "$(tname) convert $(i,FILE) to JSON if it is in NDJSON format, if $(i, FILE) is in JSON "
      ++ "format it will be converted to NDJSON. The result is printed to standard output.",
    ),
    `S(Manpage.s_bugs),
    `P("Open issue in $(i, https://github.com/mikaello/re-ndjson/issues)."),
    `S(Manpage.s_see_also),
    `P(
      "$(i, https://github.com/madnight/ndjson-to-json) and $(i, https://github.com/nypl-spacetime/json-to-ndjson)",
    ),
  ];

  (
    Term.(const(unknownFileType) $ convertFlag $ file),
    Term.info("ndjson", ~version, ~doc, ~exits=Term.default_exits, ~man),
  );
};

let _ = Term.(exit @@ eval(cmd));