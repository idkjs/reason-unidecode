let () =
  try({
    let rec loop = () => {
      read_line() |> Unidecode.decode_string |> print_endline;
      loop();
    };

    loop();
  }) {
  | End_of_file => ()
  };
