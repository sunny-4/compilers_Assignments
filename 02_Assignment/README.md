# Lexical Analyzer for C-like Language

This lexical analyzer recognizes tokens for a simplified C-like programming language as specified in the language specification document (Group ID: 22).

## Files

- `lexer.l` - Lex/Flex specification file
- `test_program.c` - Sample test program
- `compilers.txt` - Language specification document

## Features

### Keywords (22 total)
int, long, short, float, double, void, char, struct, extern, if, else, switch, case, default, for, while, do, break, continue, return, sizeof

### Operators (Every Individual Operator)

**Arithmetic Operators:**
- `+` (addition)
- `-` (subtraction)
- `*` (multiplication)
- `/` (division)
- `%` (modulus)

**Relational Operators:**
- `<` (less than)
- `>` (greater than)
- `<=` (less than or equal)
- `>=` (greater than or equal)
- `==` (equal to)
- `!=` (not equal)

**Logical Operators:**
- `&&` (logical AND)
- `||` (logical OR)

**Bitwise Operators:**
- `&` (bitwise AND)
- `|` (bitwise OR)
- `^` (bitwise XOR)
- `~` (bitwise NOT)

**Assignment Operator:**
- `=` (assignment)

**Increment/Decrement:**
- `++` (increment)
- `--` (decrement)

**Structure Access:**
- `.` (dot - member access)
- `->` (arrow - pointer member access)

**Special Operator:**
- `<=>` (three-way comparison)

### Delimiters
`(`, `)`, `{`, `}`, `[`, `]`, `;`, `,`, `:`

### Constants
- Decimal integers: `123`, `0`, `4567`
- Hexadecimal integers: `0x1234`, `0xABCD`
- Floating point: `3.14`, `0.5`, `10.0`
- Character constants: `'a'`, `'b'`, `'\n'`
- String literals: `"hello"`, `"hello world"`

### Comments
- Single-line: `// comment`
- Multi-line: `/* comment */`

### Error Handling
- Detects unclosed multi-line comments
- Reports unknown tokens

## Compilation and Usage

### On Windows (with Flex installed):

1. **Install Flex/Bison** (if not already installed):
   - Download from: https://github.com/lexxmark/winflexbison
   - Or use chocolatey: `choco install winflexbison3`

2. **Generate the lexer:**
   ```cmd
   flex lexer.l
   ```
   This creates `lex.yy.c`

3. **Compile the lexer:**
   ```cmd
   gcc lex.yy.c -o lexer.exe
   ```
   Or with MinGW:
   ```cmd
   gcc lex.yy.c -o lexer.exe -lfl
   ```

4. **Run the lexer:**
   ```cmd
   lexer.exe test_program.c
   ```
   Or from stdin:
   ```cmd
   lexer.exe
   ```
   (Type your code, press Ctrl+Z then Enter to end input)

### On Linux/Mac:

1. **Install Flex** (if not already installed):
   ```bash
   sudo apt-get install flex    # Ubuntu/Debian
   sudo yum install flex        # CentOS/RHEL
   brew install flex            # macOS
   ```

2. **Generate the lexer:**
   ```bash
   flex lexer.l
   ```

3. **Compile the lexer:**
   ```bash
   gcc lex.yy.c -o lexer -lfl
   ```

4. **Run the lexer:**
   ```bash
   ./lexer test_program.c
   ```

## Output Format

The lexer outputs tokens in the following format:

```
KEYWORD: int
IDENTIFIER: main
DELIMITER: (
DELIMITER: )
DELIMITER: {
    KEYWORD: int
    IDENTIFIER: x
    OPERATOR: =
    INTEGER_CONSTANT: 10
    DELIMITER: ;
    ...
}
```

## Testing

Use the provided `test_program.c` to test all features:

```cmd
lexer.exe test_program.c
```

## Error Examples

**Unclosed comment:**
```c
/* This comment never closes
int x = 10;
```
Output: `*** lexing terminated *** [lexer error]: ill-formed comment starting at line 1`

**Unknown token:**
```c
int x = 10 @ 5;
```
Output: `UNKNOWN TOKEN: '@' at line 1`

## Notes

- All whitespace (spaces, tabs, newlines) is ignored
- Line numbers are tracked for error reporting
- Multi-character operators are matched before single-character operators
- Hexadecimal constants are matched before decimal constants
- Keywords are case-sensitive

## Language Specification

This lexer implements the language specification defined in `compilers.txt` (Group ID: 22).
