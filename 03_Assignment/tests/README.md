# Parser Test Suite

These files are designed for `lalr_assignment3` parser input.

## Valid inputs (expected: ACCEPTED)
- `valid/01_minimal.c` — minimal `main` function.
- `valid/02_declarations_and_pointers.c` — declarations, pointers, `extern` function definition, `sizeof`.
- `valid/03_control_flow.c` — `while`, `do-while`, `for`, `if-else`, `continue`.
- `valid/04_switch_and_calls.c` — function call, relational expression, `switch/case/default`.
- `valid/05_struct_and_strings.c` — `struct` declarations, `.`, `->`, adjacent string literals, char constant.

## Invalid inputs (expected: REJECTED / lexer error)
- `invalid/01_missing_semicolon.c` — syntax error (missing `;` after declaration).
- `invalid/02_unclosed_comment.c` — lexer error (ill-formed block comment).
- `invalid/03_unsupported_operator.c` — unsupported operator (`+=`) should trigger lexer diagnostic.
- `invalid/04_malformed_switch.c` — syntax error (missing `:` in `case`).
- `invalid/05_unexpected_else.c` — syntax error (`else` without matching `if`).
