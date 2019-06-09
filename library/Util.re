let foo = () => print_endline("Ndjson is starting");

let print_results = strings => List.map(l => print_endline(l), strings);
let print_list = strings =>
  Printf.printf("Files: %s", String.concat(", ", strings));