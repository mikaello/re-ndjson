let one = () => 1;

let print_results = strings => List.map(l => print_endline(l), strings);
let print_list = strings =>
  Printf.printf("Files: %s", String.concat(", ", strings));