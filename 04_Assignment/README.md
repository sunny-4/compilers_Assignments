# CS327 Compilers - Assignment 4 (Intermediate Code Generation)

This project extends the Assignment 3 lexer and grammar to generate Intermediate Representation as Three Address Code (TAC) in quadruple format.

## Highlights

- Quadruple IR format with columns: op, arg1, arg2, result.
- Readable temporary naming: t1, t2, t3, ...
- Label-based control-flow IR: L1, L2, ...
- Supported constructs:
  - Arithmetic and relational expressions
  - Assignment statements
  - if, if-else, while, for
- Diagnostics for invalid expressions and unsupported constructs/operators.

## Project Structure

- ir_codegen.y: Bison grammar and syntax-directed TAC generation.
- ir_codegen.l: Flex lexer.
- testcases/: input programs grouped by assignment part.
  - testcases/part1: 5 testcases
  - testcases/part2: 5 testcases
  - testcases/part3: 5 testcases
  - testcases/part4: 5 testcases
- results/: generated outputs grouped by assignment part.
  - resuls/result_part1
  - resuls/result_part2
  - resuls/result_part3
  - resuls/result_part4


## Build

```bash
make
```

## Run One Testcase

```bash
./ir_codegen testcases/part1/ex1_arith.c resuls/result_part1/ex1_arith.txt
```

## Run All Testcases (All Parts)

```bash
for f in testcases/part1/*.c; do
  base=$(basename "$f" .c)
  ./ir_codegen "$f" "resuls/result_part1/${base}.txt"
done

for f in testcases/part2/*.c; do
  base=$(basename "$f" .c)
  ./ir_codegen "$f" "resuls/result_part2/${base}.txt"
done

for f in testcases/part3/*.c; do
  base=$(basename "$f" .c)
  ./ir_codegen "$f" "resuls/result_part3/${base}.txt"
done

for f in testcases/part4/*.c; do
  base=$(basename "$f" .c)
  ./ir_codegen "$f" "resuls/result_part4/${base}.txt" || true
done
```

## Output Layout

Each output report contains:

1. Input Source Program
2. Generated Intermediate Code (tabular quadruples)
3. Final status (ACCEPTED or REJECTED)
4. Diagnostics section for rejected inputs

## Assignment Scope Notes

- No optimization is performed.
- switch and do-while are intentionally reported as unsupported in this implementation.
- Unsupported operators are reported with diagnostics.
