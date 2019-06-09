open Cmdliner;
let version = "1.0.0";

let files = Arg.(value & pos_all(non_dir_file, []) & info([], ~docv="FILE"));

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
    Term.(const(ReNdjson.Util.print_results) $ files),
    Term.info("ndjson", ~version, ~doc, ~exits=Term.default_exits, ~man),
  );
};

let _ = Term.(exit @@ eval(cmd));