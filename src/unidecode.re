/* Copyright (c) 1998-2007 INRIA */
/* Copyright (c) 2018-2019 Geneanet */

let nbc = c =>
  if (Char.code(c) < 0x80) {
    1;
  } else if (Char.code(c) < 0xC0) {
    invalid_arg("nbc");
  } else if (Char.code(c) < 0xE0) {
    2;
  } else if (Char.code(c) < 0xF0) {
    3;
  } else if (Char.code(c) < 0xF8) {
    4;
  } else if (Char.code(c) < 0xFC) {
    5;
  } else if (Char.code(c) < 0xFE) {
    6;
  } else {
    invalid_arg("nbc");
  };

let decode =
    (
      fns: (int, string) => 'a,
      fnc: (int, char) => 'a,
      unsupported: int => 'a,
      s: string,
      i: int,
      len: int,
    )
    : 'a => {
  let c = String.unsafe_get(s, i);
  let nbc = nbc(c);
  let n = i + nbc;
  if (nbc < 0 || n > len) {
    fnc(i + 1, c);
  } else {
    switch (Char.code(c)) {
    /* A..Z */
    | (
        0x41 | 0x42 | 0x43 | 0x44 | 0x45 | 0x46 | 0x47 | 0x48 | 0x49 | 0x4A |
        0x4B |
        0x4C |
        0x4D |
        0x4E |
        0x4F |
        0x50 |
        0x51 |
        0x52 |
        0x53 |
        0x54 |
        0x55 |
        0x56 |
        0x57 |
        0x58 |
        0x59 |
        0x5A |
        /* a..z */
        0x61 |
        0x62 |
        0x63 |
        0x64 |
        0x65 |
        0x66 |
        0x67 |
        0x68 |
        0x69 |
        0x6A |
        0x6B |
        0x6C |
        0x6D |
        0x6E |
        0x6F |
        0x70 |
        0x71 |
        0x72 |
        0x73 |
        0x74 |
        0x75 |
        0x76 |
        0x77 |
        0x78 |
        0x79 |
        0x7A |
        /* 0..9 */
        0x30 |
        0x31 |
        0x32 |
        0x33 |
        0x34 |
        0x35 |
        0x36 |
        0x37 |
        0x38 |
        0x39
      ) as c =>
      fnc(n, Char.unsafe_chr(c))

    | 0xC2 => unsupported(n)
    | 0xC3 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80
      | 0x81
      | 0x82
      | 0x83
      | 0x84
      | 0x85 => fnc(n, 'A')
      | 0x86 => fns(n, "AE")
      | 0x87 => fnc(n, 'C')
      | 0x88
      | 0x89
      | 0x8A
      | 0x8B => fnc(n, 'E')
      | 0x8C
      | 0x8D
      | 0x8E
      | 0x8F => fnc(n, 'I')
      | 0x90 => fnc(n, 'D')
      | 0x91 => fnc(n, 'N')
      | 0x92
      | 0x93
      | 0x94
      | 0x95
      | 0x96
      | 0x98 => fnc(n, 'O')
      | 0x99
      | 0x9A
      | 0x9B
      | 0x9C => fnc(n, 'U')
      | 0x9D => fnc(n, 'Y')
      | 0x9E => fns(n, "TH")
      | 0x9F => fns(n, "sz")
      | 0xA0
      | 0xA1
      | 0xA2
      | 0xA3
      | 0xA4
      | 0xA5 => fnc(n, 'a')
      | 0xA6 => fns(n, "ae")
      | 0xA7 => fnc(n, 'c')
      | 0xA8
      | 0xA9
      | 0xAA
      | 0xAB => fnc(n, 'e')
      | 0xAC
      | 0xAD
      | 0xAE
      | 0xAF => fnc(n, 'i')
      | 0xB0 => fnc(n, 'd')
      | 0xB1 => fnc(n, 'n')
      | 0xB2
      | 0xB3
      | 0xB4
      | 0xB5
      | 0xB6
      | 0xB8 => fnc(n, 'o')
      | 0xB9
      | 0xBA
      | 0xBB
      | 0xBC => fnc(n, 'u')
      | 0xBD
      | 0xBF => fnc(n, 'y')
      | 0xBE => fns(n, "th")
      | _ => unsupported(n)
      }

    | 0xC4 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80
      | 0x82
      | 0x84 => fnc(n, 'A')
      | 0x81
      | 0x83
      | 0x85 => fnc(n, 'a')
      | 0x86
      | 0x88
      | 0x8A
      | 0x8C => fnc(n, 'C')
      | 0x87
      | 0x89
      | 0x8B
      | 0x8D => fnc(n, 'c')
      | 0x8E
      | 0x90 => fnc(n, 'D')
      | 0x8F
      | 0x91 => fnc(n, 'd')
      | 0x92
      | 0x94
      | 0x96
      | 0x98
      | 0x9A => fnc(n, 'E')
      | 0x93
      | 0x95
      | 0x97
      | 0x99
      | 0x9B => fnc(n, 'e')
      | 0x9C
      | 0x9E
      | 0xA0
      | 0xA2 => fnc(n, 'G')
      | 0x9D
      | 0x9F
      | 0xA1
      | 0xA3 => fnc(n, 'g')
      | 0xA4
      | 0xA6 => fnc(n, 'H')
      | 0xA5
      | 0xA7 => fnc(n, 'h')
      | 0xA8
      | 0xAA
      | 0xAC
      | 0xAE
      | 0xB0 => fnc(n, 'I')
      | 0xA9
      | 0xAB
      | 0xAD
      | 0xAF
      | 0xB1 => fnc(n, 'i')
      | 0xB2 => fns(n, "IJ")
      | 0xB3 => fns(n, "ij")
      | 0xB4 => fnc(n, 'J')
      | 0xB5 => fnc(n, 'j')
      | 0xB6 => fnc(n, 'K')
      | 0xB7
      | 0xB8 => fnc(n, 'k')
      | 0xB9
      | 0xBB
      | 0xBD
      | 0xBF => fnc(n, 'L')
      | 0xBA
      | 0xBC
      | 0xBE => fnc(n, 'l')
      | _ => unsupported(n)
      }

    | 0xC5 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80
      | 0x82 => fnc(n, 'l')
      | 0x81 => fnc(n, 'L')
      | 0x83
      | 0x85
      | 0x87
      | 0x8A => fnc(n, 'N')
      | 0x84
      | 0x86
      | 0x88
      | 0x89
      | 0x8B => fnc(n, 'n')
      | 0x8C
      | 0x8E
      | 0x90 => fnc(n, 'O')
      | 0x8D
      | 0x8F
      | 0x91 => fnc(n, 'o')
      | 0x92 => fns(n, "OE")
      | 0x93 => fns(n, "oe")
      | 0x94
      | 0x96
      | 0x98 => fnc(n, 'R')
      | 0x95
      | 0x97
      | 0x99 => fnc(n, 'r')
      | 0x9A
      | 0x9C
      | 0x9E
      | 0xA0 => fnc(n, 'S')
      | 0x9B
      | 0x9D
      | 0x9F
      | 0xA1 => fnc(n, 's')
      | 0xA2
      | 0xA4
      | 0xA6 => fnc(n, 'T')
      | 0xA3
      | 0xA5
      | 0xA7 => fnc(n, 't')
      | 0xA8
      | 0xAA
      | 0xAC
      | 0xAE
      | 0xB0
      | 0xB2 => fnc(n, 'U')
      | 0xA9
      | 0xAB
      | 0xAD
      | 0xAF
      | 0xB1
      | 0xB3 => fnc(n, 'u')
      | 0xB4 => fnc(n, 'W')
      | 0xB5 => fnc(n, 'w')
      | 0xB6
      | 0xB8 => fnc(n, 'Y')
      | 0xB7 => fnc(n, 'y')
      | 0xB9
      | 0xBB
      | 0xBD => fnc(n, 'Z')
      | 0xBA
      | 0xBC
      | 0xBE => fnc(n, 'z')
      | _ => unsupported(n)
      }

    | 0xC6 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x86
      | 0x9F
      | 0xA0 => fnc(n, 'O')
      | 0x90 => fnc(n, 'E')
      | 0x96
      | 0x97 => fnc(n, 'I')
      | 0xA1 => fnc(n, 'o')
      | 0xAF
      | 0xB1 => fnc(n, 'U')
      | 0xB0 => fnc(n, 'u')
      | 0xB3 => fnc(n, 'Y')
      | 0xB4 => fnc(n, 'y')
      | _ => unsupported(n)
      }

    | 0xC7 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x8D
      | 0x9E
      | 0xA0
      | 0xBA => fnc(n, 'A')
      | 0x8E
      | 0x9F
      | 0xA1
      | 0xBB => fnc(n, 'a')
      | 0x8F => fnc(n, 'I')
      | 0x90 => fnc(n, 'i')
      | 0x91
      | 0xAA
      | 0xAC
      | 0xBE => fnc(n, 'O')
      | 0x92
      | 0xAB
      | 0xAD
      | 0xBF => fnc(n, 'o')
      | 0x93
      | 0x95
      | 0x97
      | 0x99
      | 0x9B => fnc(n, 'U')
      | 0x94
      | 0x96
      | 0x98
      | 0x9A
      | 0x9C => fnc(n, 'u')
      | 0xBC
      | 0xA2 => fns(n, "AE")
      | 0xBD
      | 0xA3 => fns(n, "ae")
      | _ => unsupported(n)
      }

    | 0xC8 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80
      | 0x82
      | 0xA6
      | 0xBA => fnc(n, 'A')
      | 0x81
      | 0x83
      | 0xA7 => fnc(n, 'a')
      | 0x84
      | 0x86
      | 0xA8 => fnc(n, 'E')
      | 0x85
      | 0x87
      | 0xA9 => fnc(n, 'e')
      | 0x88
      | 0x8A => fnc(n, 'I')
      | 0x89
      | 0x8B => fnc(n, 'i')
      | 0x8C
      | 0x8E
      | 0xAA
      | 0xAC
      | 0xAE
      | 0xB0 => fnc(n, 'O')
      | 0x8D
      | 0x8F
      | 0xAB
      | 0xAD
      | 0xAF
      | 0xB1 => fnc(n, 'o')
      | 0x94
      | 0x96 => fnc(n, 'U')
      | 0x95
      | 0x97 => fnc(n, 'u')
      | 0xA2 => fns(n, "OU")
      | 0xA3 => fns(n, "ou")
      | 0xB2 => fnc(n, 'Y')
      | 0xB3 => fnc(n, 'y')
      | _ => unsupported(n)
      }

    | 0xC9 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x84 => fnc(n, 'U')
      | 0x86 => fnc(n, 'E')
      | 0x87
      | 0x9B => fnc(n, 'e')
      | 0x8E => fnc(n, 'Y')
      | 0x8F => fnc(n, 'y')
      | 0x94 => fnc(n, 'o')
      | 0xA8
      | 0xA9
      | 0xAE => fnc(n, 'i')
      | _ => unsupported(n)
      }

    | 0xCA =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x84 => fnc(n, 'u')
      | _ => unsupported(n)
      }

    /* diacritics marks */
    | 0xCC => fns(n, "")

    /* diacritics marks */
    | 0xCD when Char.code @@ String.unsafe_get(s, i + 1) <= 0xAF =>
      fns(n, "")

    | 0xCE =>
      /* Greek */
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x86 => fnc(n, 'A')
      | 0x88 => fnc(n, 'E')
      | 0x89 => fnc(n, 'H')
      | 0x8A => fnc(n, 'I')
      | 0x8C => fnc(n, 'O')
      | 0x8E => fnc(n, 'Y')
      | 0x8F => fnc(n, 'O')
      | 0x90 => fnc(n, 'I')
      | 0x91 => fnc(n, 'A')
      | 0x92 => fnc(n, 'B')
      | 0x93 => fnc(n, 'G')
      | 0x94 => fnc(n, 'D')
      | 0x95 => fnc(n, 'E')
      | 0x96 => fns(n, "DZ")
      | 0x97 => fnc(n, 'E')
      | 0x98 => fns(n, "TH")
      | 0x99 => fnc(n, 'I')
      | 0x9A => fnc(n, 'K')
      | 0x9B => fnc(n, 'L')
      | 0x9C => fnc(n, 'M')
      | 0x9D => fnc(n, 'N')
      | 0x9E => fnc(n, 'X')
      | 0x9F => fnc(n, 'O')
      | 0xA0 => fnc(n, 'P')
      | 0xA1 => fnc(n, 'R')
      | 0xA2
      | 0xA3 => fnc(n, 'S')
      | 0xA4 => fnc(n, 'T')
      | 0xA5 => fnc(n, 'U')
      | 0xA6 => fns(n, "PH")
      | 0xA7 => fns(n, "KH")
      | 0xA8 => fns(n, "PS")
      | 0xA9 => fnc(n, 'O')
      | 0xAA => fnc(n, 'I')
      | 0xAB => fnc(n, 'Y')
      | 0xAC => fnc(n, 'a')
      | 0xAD => fnc(n, 'e')
      | 0xAE => fnc(n, 'n')
      | 0xAF => fnc(n, 'i')
      | 0xB0 => fnc(n, 'a')
      | 0xB1 => fnc(n, 'a')
      | 0xB2 => fnc(n, 'b')
      | 0xB3 => fnc(n, 'g')
      | 0xB4 => fnc(n, 'd')
      | 0xB5 => fnc(n, 'e')
      | 0xB6 => fns(n, "dz")
      | 0xB7 => fnc(n, 'e')
      | 0xB8 => fns(n, "th")
      | 0xB9 => fnc(n, 'i')
      | 0xBA => fnc(n, 'k')
      | 0xBB => fnc(n, 'l')
      | 0xBC => fnc(n, 'm')
      | 0xBD => fnc(n, 'n')
      | 0xBE => fnc(n, 'x')
      | 0xBF => fnc(n, 'o')
      | _ => unsupported(n)
      }

    | 0xCF =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80 => fnc(n, 'p')
      | 0x81 => fnc(n, 'r')
      | 0x82
      | 0x83 => fnc(n, 's')
      | 0x84 => fnc(n, 't')
      | 0x85 => fnc(n, 'u')
      | 0x86 => fns(n, "ph")
      | 0x87 => fns(n, "kh")
      | 0x88 => fns(n, "ps")
      | 0x89
      | 0x8C
      | 0x8E => fnc(n, 'o')
      | 0x8A => fnc(n, 'i')
      | 0x8B
      | 0x8D => fnc(n, 'u')
      | _ => unsupported(n)
      }

    | 0xD0 =>
      /* Cyrillic */
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x81 => fnc(n, 'E')
      | 0x86 => fnc(n, 'I')
      | 0x90 => fnc(n, 'A')
      | 0x91 => fnc(n, 'B')
      | 0x92 => fnc(n, 'V')
      | 0x93 => fnc(n, 'G')
      | 0x94 => fnc(n, 'D')
      | 0x95 => fnc(n, 'E')
      | 0x96 => fnc(n, 'J')
      | 0x97 => fnc(n, 'Z')
      | 0x98
      | 0x99 => fnc(n, 'I')
      | 0x9A => fnc(n, 'K')
      | 0x9B => fnc(n, 'L')
      | 0x9C => fnc(n, 'M')
      | 0x9D => fnc(n, 'N')
      | 0x9E => fnc(n, 'O')
      | 0x9F => fnc(n, 'P')
      | 0xA0 => fnc(n, 'R')
      | 0xA1 => fnc(n, 'S')
      | 0xA2 => fnc(n, 'T')
      | 0xA3 => fns(n, "OU")
      | 0xA4 => fnc(n, 'F')
      | 0xA5 => fns(n, "KH")
      | 0xA6 => fns(n, "TS")
      | 0xA7 => fns(n, "TCH")
      | 0xA8 => fns(n, "CH")
      | 0xA9 => fns(n, "CHT")
      | 0xAB => fnc(n, 'Y')
      | 0xAD => fnc(n, 'E')
      | 0xAE => fns(n, "YOU")
      | 0xAF => fns(n, "YA")
      | 0xB0 => fnc(n, 'a')
      | 0xB1 => fnc(n, 'b')
      | 0xB2 => fnc(n, 'v')
      | 0xB3 => fnc(n, 'g')
      | 0xB4 => fnc(n, 'd')
      | 0xB5 => fnc(n, 'e')
      | 0xB6 => fnc(n, 'j')
      | 0xB7 => fnc(n, 'z')
      | 0xB8
      | 0xB9 => fnc(n, 'i')
      | 0xBA => fnc(n, 'k')
      | 0xBB => fnc(n, 'l')
      | 0xBC => fnc(n, 'm')
      | 0xBD => fnc(n, 'n')
      | 0xBE => fnc(n, 'o')
      | 0xBF => fnc(n, 'p')
      | _ => unsupported(n)
      }

    | 0xD1 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80 => fnc(n, 'r')
      | 0x81 => fnc(n, 's')
      | 0x82 => fnc(n, 't')
      | 0x83 => fns(n, "ou")
      | 0x84 => fnc(n, 'f')
      | 0x85 => fns(n, "kh")
      | 0x86 => fns(n, "ts")
      | 0x87 => fns(n, "tch")
      | 0x88 => fns(n, "ch")
      | 0x89 => fns(n, "cht")
      | 0x8B => fnc(n, 'y')
      | 0x8C => fnc(n, '\'')
      | 0x8D => fnc(n, 'e')
      | 0x8E => fns(n, "yu")
      | 0x8F => fns(n, "ya")
      | 0x91 => fnc(n, 'e')
      | _ => unsupported(n)
      }

    | 0xD2 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0xAf => fnc(n, 'u')
      | _ => unsupported(n)
      }

    | 0xD3 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80 => fnc(n, 'I')
      | 0x95 => fns(n, "ae")
      | _ => unsupported(n)
      }

    | 0xD4 =>
      /* Armenian */
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0xB1 => fnc(n, 'A')
      | 0xB2 => fnc(n, 'B')
      | 0xB3 => fnc(n, 'G')
      | 0xB4 => fnc(n, 'D')
      | 0xB5 => fnc(n, 'E')
      | 0xB6 => fnc(n, 'Z')
      | 0xB7 => fnc(n, 'E')
      | 0xB8 => fnc(n, 'E')
      | 0xB9 => fnc(n, 'T')
      | 0xBA => fnc(n, 'Z')
      | 0xBB => fnc(n, 'I')
      | 0xBC => fnc(n, 'L')
      | 0xBD => fnc(n, 'X')
      | 0xBE => fnc(n, 'C')
      | 0xBF => fnc(n, 'K')
      | _ => unsupported(n)
      }

    | 0xD5 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80 => fnc(n, 'H')
      | 0x81 => fnc(n, 'J')
      | 0x82 => fnc(n, 'L')
      | 0x83 => fnc(n, 'C')
      | 0x84 => fnc(n, 'M')
      | 0x85 => fnc(n, 'Y')
      | 0x86 => fnc(n, 'N')
      | 0x87 => fnc(n, 'S')
      | 0x88 => fnc(n, 'O')
      | 0x89 => fnc(n, 'C')
      | 0x8A => fnc(n, 'P')
      | 0x8B => fnc(n, 'J')
      | 0x8C => fnc(n, 'R')
      | 0x8D => fnc(n, 'S')
      | 0x8E => fnc(n, 'V')
      | 0x8F => fnc(n, 'T')
      | 0x90 => fnc(n, 'R')
      | 0x91 => fnc(n, 'C')
      | 0x92 => fnc(n, 'W')
      | 0x93 => fnc(n, 'P')
      | 0x94 => fnc(n, 'K')
      | 0x95 => fnc(n, 'O')
      | 0x96 => fnc(n, 'F')
      | 0xA1 => fnc(n, 'a')
      | 0xA2 => fnc(n, 'b')
      | 0xA3 => fnc(n, 'g')
      | 0xA4 => fnc(n, 'd')
      | 0xA5 => fnc(n, 'e')
      | 0xA6 => fnc(n, 'z')
      | 0xA7 => fnc(n, 'e')
      | 0xA8 => fnc(n, 'e')
      | 0xA9 => fnc(n, 't')
      | 0xAA => fnc(n, 'z')
      | 0xAB => fnc(n, 'i')
      | 0xAC => fnc(n, 'l')
      | 0xAD => fnc(n, 'x')
      | 0xAE => fnc(n, 'c')
      | 0xAF => fnc(n, 'k')
      | 0xB0 => fnc(n, 'h')
      | 0xB1 => fnc(n, 'j')
      | 0xB2 => fnc(n, 'l')
      | 0xB3 => fnc(n, 'c')
      | 0xB4 => fnc(n, 'm')
      | 0xB5 => fnc(n, 'y')
      | 0xB6 => fnc(n, 'n')
      | 0xB7 => fnc(n, 's')
      | 0xB8 => fnc(n, 'o')
      | 0xB9 => fnc(n, 'c')
      | 0xBA => fnc(n, 'p')
      | 0xBB => fnc(n, 'j')
      | 0xBC => fnc(n, 'r')
      | 0xBD => fnc(n, 's')
      | 0xBE => fnc(n, 'v')
      | 0xBF => fnc(n, 't')
      | _ => unsupported(n)
      }

    | 0xD6 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80 => fnc(n, 'r')
      | 0x81 => fnc(n, 'c')
      | 0x82 => fnc(n, 'w')
      | 0x83 => fnc(n, 'p')
      | 0x84 => fnc(n, 'k')
      | 0x85 => fnc(n, 'o')
      | 0x86 => fnc(n, 'f')
      | _ => unsupported(n)
      }

    | 0xE1 =>
      /* Vietnameese */
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0xB5 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0xAB => fns(n, "ue")
        | 0xBC => fnc(n, 'i')
        | 0xBF => fnc(n, 'u')
        | _ => unsupported(n)
        }
      | 0xB6 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x8F
        | 0x90 => fnc(n, 'a')
        | 0x92 => fnc(n, 'e')
        | 0x96 => fnc(n, 'i')
        | 0x97 => fnc(n, 'o')
        | 0x99 => fnc(n, 'u')
        | _ => unsupported(n)
        }
      | 0xB8 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x80 => fnc(n, 'A')
        | 0x81 => fnc(n, 'a')
        | 0x82 => fnc(n, 'B')
        | 0x83 => fnc(n, 'b')
        | 0x84 => fnc(n, 'B')
        | 0x85 => fnc(n, 'b')
        | 0x86 => fnc(n, 'B')
        | 0x87 => fnc(n, 'b')
        | 0x88 => fnc(n, 'C')
        | 0x89 => fnc(n, 'c')
        | 0x8A => fnc(n, 'D')
        | 0x8B => fnc(n, 'd')
        | 0x8C => fnc(n, 'D')
        | 0x8D => fnc(n, 'd')
        | 0x8E => fnc(n, 'D')
        | 0x8F => fnc(n, 'd')
        | 0x90 => fnc(n, 'D')
        | 0x91 => fnc(n, 'd')
        | 0x92 => fnc(n, 'D')
        | 0x93 => fnc(n, 'd')
        | 0x94 => fnc(n, 'E')
        | 0x95 => fnc(n, 'e')
        | 0x96 => fnc(n, 'E')
        | 0x97 => fnc(n, 'e')
        | 0x98 => fnc(n, 'E')
        | 0x99 => fnc(n, 'e')
        | 0x9A => fnc(n, 'E')
        | 0x9B => fnc(n, 'e')
        | 0x9C => fnc(n, 'E')
        | 0x9D => fnc(n, 'e')
        | 0x9E => fnc(n, 'F')
        | 0x9F => fnc(n, 'f')
        | 0xA0 => fnc(n, 'F')
        | 0xA1 => fnc(n, 'f')
        | 0xA2 => fnc(n, 'G')
        | 0xA3 => fnc(n, 'g')
        | 0xA4 => fnc(n, 'H')
        | 0xA5 => fnc(n, 'h')
        | 0xA6 => fnc(n, 'H')
        | 0xA7 => fnc(n, 'h')
        | 0xA8 => fnc(n, 'H')
        | 0xA9 => fnc(n, 'h')
        | 0xAA => fnc(n, 'H')
        | 0xAB => fnc(n, 'h')
        | 0xAC => fnc(n, 'I')
        | 0xAD => fnc(n, 'i')
        | 0xAE => fnc(n, 'I')
        | 0xAF => fnc(n, 'i')
        | 0xB0 => fnc(n, 'K')
        | 0xB1 => fnc(n, 'k')
        | 0xB2 => fnc(n, 'K')
        | 0xB3 => fnc(n, 'k')
        | 0xB4 => fnc(n, 'K')
        | 0xB5 => fnc(n, 'k')
        | 0xB6 => fnc(n, 'L')
        | 0xB7 => fnc(n, 'l')
        | 0xB8 => fnc(n, 'L')
        | 0xB9 => fnc(n, 'l')
        | 0xBA => fnc(n, 'L')
        | 0xBB => fnc(n, 'l')
        | 0xBC => fnc(n, 'L')
        | 0xBD => fnc(n, 'l')
        | 0xBE => fnc(n, 'M')
        | 0xBF => fnc(n, 'm')
        | _ => unsupported(n)
        }
      | 0xB9 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x80 => fnc(n, 'M')
        | 0x81 => fnc(n, 'm')
        | 0x82 => fnc(n, 'M')
        | 0x83 => fnc(n, 'm')
        | 0x84 => fnc(n, 'N')
        | 0x85 => fnc(n, 'n')
        | 0x86 => fnc(n, 'N')
        | 0x87 => fnc(n, 'n')
        | 0x88 => fnc(n, 'N')
        | 0x89 => fnc(n, 'n')
        | 0x8A => fnc(n, 'N')
        | 0x8B => fnc(n, 'n')
        | 0x8C => fnc(n, 'O')
        | 0x8D => fnc(n, 'o')
        | 0x8E => fnc(n, 'O')
        | 0x8F => fnc(n, 'o')
        | 0x90 => fnc(n, 'O')
        | 0x91 => fnc(n, 'o')
        | 0x92 => fnc(n, 'O')
        | 0x93 => fnc(n, 'o')
        | 0x94 => fnc(n, 'P')
        | 0x95 => fnc(n, 'p')
        | 0x96 => fnc(n, 'P')
        | 0x97 => fnc(n, 'p')
        | 0x98 => fnc(n, 'R')
        | 0x99 => fnc(n, 'r')
        | 0x9A => fnc(n, 'R')
        | 0x9B => fnc(n, 'r')
        | 0x9C => fnc(n, 'R')
        | 0x9D => fnc(n, 'r')
        | 0x9E => fnc(n, 'R')
        | 0x9F => fnc(n, 'r')
        | 0xA0 => fnc(n, 'S')
        | 0xA1 => fnc(n, 's')
        | 0xA2 => fnc(n, 'S')
        | 0xA3 => fnc(n, 's')
        | 0xA4 => fnc(n, 'S')
        | 0xA5 => fnc(n, 's')
        | 0xA6 => fnc(n, 'S')
        | 0xA7 => fnc(n, 's')
        | 0xA8 => fnc(n, 'S')
        | 0xA9 => fnc(n, 's')
        | 0xAA => fnc(n, 'T')
        | 0xAB => fnc(n, 't')
        | 0xAC => fnc(n, 'T')
        | 0xAD => fnc(n, 't')
        | 0xAE => fnc(n, 'T')
        | 0xAF => fnc(n, 't')
        | 0xB0 => fnc(n, 'T')
        | 0xB1 => fnc(n, 't')
        | 0xB2 => fnc(n, 'U')
        | 0xB3 => fnc(n, 'u')
        | 0xB4 => fnc(n, 'U')
        | 0xB5 => fnc(n, 'u')
        | 0xB6 => fnc(n, 'U')
        | 0xB7 => fnc(n, 'u')
        | 0xB8 => fnc(n, 'U')
        | 0xB9 => fnc(n, 'u')
        | 0xBA => fnc(n, 'U')
        | 0xBB => fnc(n, 'u')
        | 0xBC => fnc(n, 'V')
        | 0xBD => fnc(n, 'v')
        | 0xBE => fnc(n, 'V')
        | 0xBF => fnc(n, 'v')
        | _ => unsupported(n)
        }
      | 0xBA =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x80 => fnc(n, 'W')
        | 0x81 => fnc(n, 'w')
        | 0x82 => fnc(n, 'W')
        | 0x83 => fnc(n, 'w')
        | 0x84 => fnc(n, 'W')
        | 0x85 => fnc(n, 'w')
        | 0x86 => fnc(n, 'W')
        | 0x87 => fnc(n, 'w')
        | 0x88 => fnc(n, 'W')
        | 0x89 => fnc(n, 'w')
        | 0x8A => fnc(n, 'X')
        | 0x8B => fnc(n, 'x')
        | 0x8C => fnc(n, 'X')
        | 0x8D => fnc(n, 'x')
        | 0x8E => fnc(n, 'Y')
        | 0x8F => fnc(n, 'y')
        | 0x90 => fnc(n, 'Z')
        | 0x91 => fnc(n, 'z')
        | 0x92 => fnc(n, 'Z')
        | 0x93 => fnc(n, 'z')
        | 0x94 => fnc(n, 'Z')
        | 0x95 => fnc(n, 'z')
        | 0x96 => fnc(n, 'h')
        | 0x97 => fnc(n, 't')
        | 0x98 => fnc(n, 'w')
        | 0x99 => fnc(n, 'y')
        | 0x9A => fnc(n, 'a')
        | 0x9B => fnc(n, 's')
        | 0x9C => fnc(n, 's')
        | 0x9D => fnc(n, 'r')
        | 0x9E => fnc(n, 's')
        | 0x9F => fnc(n, 'd')
        | 0xA0 => fnc(n, 'A')
        | 0xA1 => fnc(n, 'a')
        | 0xA2 => fnc(n, 'A')
        | 0xA3 => fnc(n, 'a')
        | 0xA4 => fnc(n, 'A')
        | 0xA5 => fnc(n, 'a')
        | 0xA6 => fnc(n, 'A')
        | 0xA7 => fnc(n, 'a')
        | 0xA8 => fnc(n, 'A')
        | 0xA9 => fnc(n, 'a')
        | 0xAA => fnc(n, 'A')
        | 0xAB => fnc(n, 'a')
        | 0xAC => fnc(n, 'A')
        | 0xAD => fnc(n, 'a')
        | 0xAE => fnc(n, 'A')
        | 0xAF => fnc(n, 'a')
        | 0xB0 => fnc(n, 'A')
        | 0xB1 => fnc(n, 'a')
        | 0xB2 => fnc(n, 'A')
        | 0xB3 => fnc(n, 'a')
        | 0xB4 => fnc(n, 'A')
        | 0xB5 => fnc(n, 'a')
        | 0xB6 => fnc(n, 'A')
        | 0xB7 => fnc(n, 'a')
        | 0xB8 => fnc(n, 'E')
        | 0xB9 => fnc(n, 'e')
        | 0xBA => fnc(n, 'E')
        | 0xBB => fnc(n, 'e')
        | 0xBC => fnc(n, 'E')
        | 0xBD => fnc(n, 'e')
        | 0xBE => fnc(n, 'E')
        | 0xBF => fnc(n, 'e')
        | _ => unsupported(n)
        }
      | 0xBB =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x80 => fnc(n, 'E')
        | 0x81 => fnc(n, 'e')
        | 0x82 => fnc(n, 'E')
        | 0x83 => fnc(n, 'e')
        | 0x84 => fnc(n, 'E')
        | 0x85 => fnc(n, 'e')
        | 0x86 => fnc(n, 'E')
        | 0x87 => fnc(n, 'e')
        | 0x88 => fnc(n, 'I')
        | 0x89 => fnc(n, 'i')
        | 0x8A => fnc(n, 'I')
        | 0x8B => fnc(n, 'i')
        | 0x8C => fnc(n, 'O')
        | 0x8D => fnc(n, 'o')
        | 0x8E => fnc(n, 'O')
        | 0x8F => fnc(n, 'o')
        | 0x90 => fnc(n, 'O')
        | 0x91 => fnc(n, 'o')
        | 0x92 => fnc(n, 'O')
        | 0x93 => fnc(n, 'o')
        | 0x94 => fnc(n, 'O')
        | 0x95 => fnc(n, 'o')
        | 0x96 => fnc(n, 'O')
        | 0x97 => fnc(n, 'o')
        | 0x98 => fnc(n, 'O')
        | 0x99 => fnc(n, 'o')
        | 0x9A => fnc(n, 'O')
        | 0x9B => fnc(n, 'o')
        | 0x9C => fnc(n, 'O')
        | 0x9D => fnc(n, 'o')
        | 0x9E => fnc(n, 'O')
        | 0x9F => fnc(n, 'o')
        | 0xA0 => fnc(n, 'O')
        | 0xA1 => fnc(n, 'o')
        | 0xA2 => fnc(n, 'O')
        | 0xA3 => fnc(n, 'o')
        | 0xA4 => fnc(n, 'U')
        | 0xA5 => fnc(n, 'u')
        | 0xA6 => fnc(n, 'U')
        | 0xA7 => fnc(n, 'u')
        | 0xA8 => fnc(n, 'U')
        | 0xA9 => fnc(n, 'u')
        | 0xAA => fnc(n, 'U')
        | 0xAB => fnc(n, 'u')
        | 0xAC => fnc(n, 'U')
        | 0xAD => fnc(n, 'u')
        | 0xAE => fnc(n, 'U')
        | 0xAF => fnc(n, 'u')
        | 0xB0 => fnc(n, 'U')
        | 0xB1 => fnc(n, 'u')
        | 0xB2 => fnc(n, 'Y')
        | 0xB3 => fnc(n, 'y')
        | 0xB4 => fnc(n, 'Y')
        | 0xB5 => fnc(n, 'y')
        | 0xB6 => fnc(n, 'Y')
        | 0xB7 => fnc(n, 'y')
        | 0xB8 => fnc(n, 'Y')
        | 0xB9 => fnc(n, 'y')
        | 0xBE => fnc(n, 'Y')
        | 0xBF => fnc(n, 'y')
        | _ => unsupported(n)
        }
      | _ => unsupported(n)
      } /* 0xE1 */

    | 0xE2 =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x80 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x90
        | 0x91
        | 0x92
        | 0x93 => fnc(n, '-')
        | 0x94
        | 0x95 => fns(n, "--")
        | 0x99 => fnc(n, '\'')
        | _ => unsupported(n)
        }
      | 0x84 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0xB4 => fnc(n, 'o')
        | _ => unsupported(n)
        }
      | 0xB1 =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0xA5 => fnc(n, 'a')
        | 0xAD => fnc(n, 'A')
        | 0xBA => fnc(n, 'o')
        | 0xB8 => fnc(n, 'e')
        | _ => unsupported(n)
        }
      | _ => unsupported(n)
      }

    | 0xEA =>
      switch (Char.code @@ String.unsafe_get(s, i + 1)) {
      | 0x9D =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x8A
        | 0x8C => fnc(n, 'O')
        | 0x8B
        | 0x8D => fnc(n, 'o')
        | 0x8F => fns(n, "oo")
        | 0x8E => fns(n, "OO")
        | 0xB8 => fns(n, "um")
        | _ => unsupported(n)
        }
      | 0x9E =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0xB6 => fnc(n, 'O')
        | 0xB7 => fnc(n, 'o')
        | _ => unsupported(n)
        }
      | 0xAC =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0xBF => fnc(n, 'o')
        | _ => unsupported(n)
        }
      | 0xAD =>
        switch (Char.code @@ String.unsafe_get(s, i + 2)) {
        | 0x80
        | 0xA2 => fns(n, "oe")
        | 0x8E
        | 0x8F
        | 0x92 => fnc(n, 'u')
        | 0x90 => fns(n, "ui")
        | 0x9A => fnc(n, 'y')
        | 0xA3 => fns(n, "uo")
        | _ => unsupported(n)
        }
      | _ => unsupported(n)
      }

    | _ => unsupported(n)
    };
  };
};

let string_forall = (fn, s) => {
  let len = String.length(s) - 1;
  let rec loop = i =>
    if (i == len) {
      true;
    } else {
      fn(String.unsafe_get(s, i)) && loop(i + 1);
    };
  loop(0);
};

let decode_string = (~unsupported=?, s) =>
  if (string_forall(c => Char.code(c) < 128, s)) {
    s;
  } else {
    let b = Bytes.create(String.length(s) * 2);
    let unsupported =
      switch (unsupported) {
      | Some(fn) => fn
      | None => (
          (b, i, n, o) => {
            Bytes.blit_string(s, i, b, o^, n - i);
            o := o^ + n - i;
          }
        )
      };

    let o = ref(0);
    /* decode returns at max a string of 3 characters instead of 2
       (e.g. "\0xd0\0xa7" -> "TCH" */
    let len = String.length(s);
    let rec loop = i =>
      if (i >= len) {
        Bytes.sub_string(b, 0, o^);
      } else {
        loop @@
        decode(
          (n, s) => {
            Bytes.blit_string(s, 0, b, o^, String.length(s));
            o := o^ + String.length(s);
            n;
          },
          (n, c) => {
            Bytes.unsafe_set(b, o^, c);
            incr(o);
            n;
          },
          n => {
            unsupported(b, i, n, o);
            n;
          },
          s,
          i,
          len,
        );
      };

    loop(0);
  };
