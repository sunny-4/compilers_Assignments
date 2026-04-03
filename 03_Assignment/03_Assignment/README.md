# CS327 Compilers - Lab Assignment 3

## LALR(1) Parser Construction and Conflict Resolution

This repository contains an implementation of Assignment 3 for **CS327 Compilers**.
It includes:
- original grammar and lexer,
- conflict-resolved grammar and lexer,
- parser reports for each part,
- test programs (valid + invalid),
- commands to verify each assignment requirement.

## Current project mode

- `lalr_assignment3.y` = **unresolved/conflict grammar** (used for Part 1 conflict demonstration)
- `lalr_assignment3_resolved.y` = **resolved grammar** (used for Parts 2–6 runtime features)

---


## What this assignment does

### Part 1
- Constructs LALR(1) automaton from grammar.
- Identifies parser conflicts.
- Shows conflict state, type, and productions.

### Part 2
- Resolves identified conflicts .
- Validates conflict removal with before/after parser generation.
- Demonstrates parsing behavior on example inputs.

### Part 3
- Stores derivation (reduction sequence) while parsing.
- Prints derivation in reverse order after successful parsing.

### Part 4
- Prints LALR(1) parsing table in matrix/tabular form.
- Uses lecture-style action notation: `sN`, `rK`, `acc`.

### Part 5
- Provides informative error diagnostics:
  - line/column,
  - unexpected token/lexeme,
  - source line + caret,
  - fix hints.

### Part 6
- Adds implementation analysis, limitations, and future improvements.

---

## Important files

### Core parser/lexer files
- `lalr_assignment3.y` - original grammar
- `lalr_assignment3.l` - original lexer
- `lalr_assignment3_resolved.y` - conflict-resolved grammar (main submission grammar)
- `lalr_assignment3_resolved.l` - conflict-resolved lexer

> Note: Both lexer files use the same tokenization behavior; only the parser header include differs
> (`lalr_assignment3.tab.h` vs `lalr_assignment3_resolved.tab.h`).

### Generated automaton/report artifacts
- `lalr_assignment3.output` - original automaton (shows conflict)
- `lalr_assignment3_resolved.output` - resolved automaton (no conflict)

### Part-wise writeups
- `reports/part1/conflict_report.txt` - conflict state/type/productions
- `reports/part2/part2_conflict_resolution_report.txt`
- `reports/part3/part3_reverse_derivation_report.txt`
- `reports/part4/part4_parsing_table_report.txt`
- `reports/part5/part5_error_diagnostics_report.txt`
- `reports/part6/part6_additional_information.txt`

### Test suite
- `tests/valid/` - expected accepted inputs
- `tests/invalid/` - expected rejected inputs
- `tests/conflict_examples/` - examples for conflict resolution discussion

---

## Build instructions

### Build unresolved parser (Part 1 conflict demonstration)

```bash
bison -d lalr_assignment3.y
flex -o lex.yy.c lalr_assignment3.l
gcc lalr_assignment3.tab.c lex.yy.c -o unresolved -lfl
```

### Build resolved parser (Parts 2--6 final behavior)

```bash
bison -d -b lalr_assignment3_resolved lalr_assignment3_resolved.y
flex -o lex_resolved.yy.c lalr_assignment3_resolved.l
gcc lalr_assignment3_resolved.tab.c lex_resolved.yy.c -o lalr_parser_resolved -lfl
```

### Build both in one go

```bash
bison -d lalr_assignment3.y
flex -o lex.yy.c lalr_assignment3.l
gcc lalr_assignment3.tab.c lex.yy.c -o unresolved -lfl
bison -d -b lalr_assignment3_resolved lalr_assignment3_resolved.y
flex -o lex_resolved.yy.c lalr_assignment3_resolved.l
gcc lalr_assignment3_resolved.tab.c lex_resolved.yy.c -o lalr_parser_resolved -lfl
```

---

## Run parser on one file

### Run unresolved parser

```bash
./unresolved tests/conflict_examples/dangling_else.c reports/part1/unresolved_run_report.txt
```

### Run resolved parser

```bash
./lalr_parser_resolved tests/valid/01_minimal.c reports/part3/run_report.txt
```

Output behavior:
- Terminal: parsing table, reductions, result, reverse derivation (on success).
- output report file (e.g., in `reports/partX/...`): same information saved to file.

---

## Quick verification commands (Part-wise)

## Part 1: Automaton + conflict identification

```bash
bison -Wall -Wconflicts-sr -Wconflicts-rr -v -d lalr_assignment3.y
grep -n "conflicts:" lalr_assignment3.output
cat reports/part1/conflict_report.txt
```

Expected:
- multiple shift/reduce conflicts in unresolved grammar (`lalr_assignment3.y`),
  currently 363 SR conflicts and 0 RR conflicts.
- conflict details present in `conflict_report.txt`.

## Part 2: Conflict resolution

```bash
bison -Wall -Wconflicts-sr -Wconflicts-rr -v -d -b lalr_assignment3_resolved lalr_assignment3_resolved.y
grep -n "conflicts:" lalr_assignment3_resolved.output || true
cat reports/part2/part2_conflict_resolution_report.txt
```

Expected:
- no conflict entry in resolved `.output`.

Optional direct compare:

```bash
grep -n "conflicts:" lalr_assignment3.output | head -n 5
grep -n "conflicts:" lalr_assignment3_resolved.output || true
```

## Part 3: Reverse derivation tree

```bash
./lalr_parser_resolved tests/valid/01_minimal.c reports/part3/part3_check_report.txt
grep -n "Result:\|Reverse Derivation Tree" reports/part3/part3_check_report.txt
```

Expected:
- `Result: ACCEPTED`
- `Reverse Derivation Tree (Reduction Sequence in Reverse)` present.

## Part 4: Parsing table matrix output

```bash
./lalr_parser_resolved tests/valid/01_minimal.c reports/part4/part4_table_report.txt
grep -n "LALR(1) Parsing Table (Matrix Format)" reports/part4/part4_table_report.txt
```

Expected:
- matrix table header exists.
- state/action-goto rows are shown under the header.

## Part 5: Error diagnostics

```bash
./lalr_parser_resolved tests/invalid/04_malformed_switch.c reports/part5/error_report.txt
grep -n "\[ERROR\]\|Unexpected token/lexeme\|Source line\|Hint:\|Result:" reports/part5/error_report.txt
```

Expected:
- detailed syntax error diagnostics with hint.
- includes line/column, unexpected lexeme, source line, and a hint.

## Part 6: Additional information

```bash
cd /home/set-iitgn-vm/Downloads/compilersfiles
cat reports/part6/part6_additional_information.txt
```

Expected:
- implementation analysis and extra notes.

---

## Optional: run all tests quickly

```bash
cd /home/set-iitgn-vm/Downloads/compilersfiles
for f in tests/valid/*.c; do echo "=== VALID: $f ==="; ./lalr_parser_resolved "$f" "/tmp/$(basename "$f").report" | tail -n 2; done
for f in tests/invalid/*.c; do echo "=== INVALID: $f ==="; ./lalr_parser_resolved "$f" "/tmp/$(basename "$f").report" | tail -n 4; done
```

---

## Notes

- Use `lalr_assignment3_resolved.y` for final evaluation/demo.
- `lalr_assignment3.y` is intentionally kept ambiguous for conflict analysis in Part 1.
- `lalr_assignment3_resolved.y` is the final conflict-free parser used for Part 2 onward.
- Executables commonly used in this repository:
  - `unresolved` (from `lalr_assignment3.y`)
  - `lalr_parser_resolved` (from `lalr_assignment3_resolved.y`)
  - `a.out` can still be used if you compile without `-o`.
