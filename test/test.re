open OUnit2;
open Test_data;

let test_decode_string = (exp, inp) =>
  assert_equal(~printer=x => x, exp, Unidecode.decode_string(inp));

let _ =
  run_test_tt_main(
    "Unidecode"
    >::: [
      "decode_string french"
      >:: (_ => test_decode_string(french_expected, french_input)),
      "decode_string vietnamese"
      >:: (_ => test_decode_string(vietnamese_expected, vietnamese_input)),
      "decode_string russian"
      >:: (_ => test_decode_string(russian_expected, russian_input)),
    ],
  );
