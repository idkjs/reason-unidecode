module B = Benchmark;
module D = Test_data;

let bench = (name, input) => {
  let aux = (name, fn) => B.throughput1(~style=B.Nil, ~name, 1, fn, input);
  let s1 = aux("Unidecode", Unidecode.decode_string);
  let s2 = aux("Ubase", Ubase.from_utf8_string);
  print_newline();
  print_endline(name);
  B.tabulate @@ B.merge(s1, s2);
};

let _ = {
  bench("French", D.french_input);
  bench("Vietnamese", D.vietnamese_input);
};
