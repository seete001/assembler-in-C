# Simple Assembler (Educational Project)

A small educational assembler written in C.

This project started as a simple experiment that converted a few assembly-like instructions into hexadecimal output. It has evolved into a structured assembler pipeline with its own lexer, token system, parser, intermediate representation, assembler backend, file input/output system, and binary machine-code generation.

The goal of this project is not to replicate a real CPU assembler, but to understand how assemblers are designed internally and how source code is transformed into executable instructions.

---

# Project Evolution

## Version 1 — Simple Line-Based Assembler

The first version was a minimal assembler prototype.

It:

* Read an assembly file line by line
* Used `sscanf()` to extract instruction arguments
* Used lookup tables for instructions and registers
* Converted instructions into a fixed byte format

Example:

```asm
ADD eax, 2
```

became:

```
83 00 02
```

The pipeline was:

```
Assembly file
      |
      v
 sscanf()
      |
      v
Opcode lookup
      |
      v
Register lookup
      |
      v
Hex output
```

## Limitations of the first version

The first implementation had many restrictions:

* Very strict input format
* Only register + immediate instructions
* No register-to-register operations
* No labels
* No memory addressing
* No structured parsing
* No meaningful error reporting
* No separation between different assembler stages

Although limited, this version provided the foundation for understanding assembler design.

---

# Version 2 — Structured Assembler Architecture

The project was redesigned into separate compiler-like stages.

The new pipeline is:

```
Assembly Source (.asm)

        |
        v

    File Reader

        |
        v

      Lexer

        |
        v

      Tokens

        |
        v

      Parser

        |
        v

  Instruction Program

        |
        v

    Assembler

        |
        v

   Machine Code

        |
        v

    Binary File
```

Each stage has a specific responsibility.

---

# Current Features

## File Input / Output

The assembler can now read real assembly files.

Example:

```
program.asm
```

is loaded into memory, processed through the assembler pipeline, and converted into:

```
program.bin
```

The output is stored as raw binary bytes.

---

# Lexer

The lexer scans the source code and converts characters into tokens.

Supported tokens:

* Identifiers
* Numbers
* Commas
* Colons
* Brackets
* New lines
* End of file

Example:

Input:

```asm
MOV r1, r2
```

Tokens:

```
IDENTIFIER  MOV
IDENTIFIER  r1
COMMA
IDENTIFIER  r2
```

---

# Token System

Tokens contain:

* Token type
* Token value
* Line number
* Column number

This allows better debugging and future error reporting.

Example:

```
IDENTIFIER: MOV (line 1, column 0)
```

---

# Parser

The parser converts tokens into structured instructions.

Instead of directly manipulating strings, the assembler creates an internal representation.

Example:

```asm
MOV r1, r2
```

becomes:

```
Instruction

Opcode:
    MOV

Operands:
    r1
    r2
```

---

# Operand System

Operands are classified by type:

```c
OP_REGISTER
OP_IMMEDIATE
OP_LABEL
OP_MEMORY
```

Examples:

```
r1        -> REGISTER

10        -> IMMEDIATE

loop      -> LABEL

[address] -> MEMORY
```

Currently implemented:

* Registers
* Immediate values
* Labels (parsing support)

---

# Instruction Representation

Instructions are stored using structures:

```c
Instruction
{
    opcode

    operands[2]

    operand_count
}
```

This design allows different instruction formats to be added later.

---

# Program Parsing

The parser can process complete programs containing multiple instructions.

Example:

```asm
MOV r1, r2
ADD r3, 5
JMP loop
```

becomes:

```
Program

Instruction 0:
    MOV
    r1
    r2


Instruction 1:
    ADD
    r3
    5


Instruction 2:
    JMP
    loop
```

---

# Opcode System

Instructions are separated into their own opcode table.

Example:

```
MOV -> 0x01
ADD -> 0x02
SUB -> 0x03
JMP -> 0x06
```

This allows instructions to be expanded without changing the parser.

---

# Machine Code Generation

The assembler converts instructions into bytes.

Example:

Assembly:

```asm
MOV r1, r2
```

Generated machine code:

```
01 01 02
```

Format:

```
opcode
operand 1
operand 2
```

This is a custom educational encoding format.

---

# Binary Output

The assembler now produces real binary output.

Example:

Input:

```asm
MOV r1, r2
ADD r3, 5
```

Output:

```
program.bin
```

Inspecting the file:

```
01 01 02
02 03 05
```

The generated file contains raw bytes instead of text.

---

# Build System

The project uses a Makefile.

Build:

```bash
make
```

Run:

```bash
make run
```

Clean:

```bash
make clean
```

Project build structure:

```
assembler/

├── bin/
│   └── assembler
│
├── build/
│   └── object files
│
├── include/
│
├── src/
│
└── tests/
```

---

# Current Project Structure

```
assembler/

├── include/
│   ├── lexer.h
│   ├── token.h
│   ├── parser.h
│   ├── instruction.h
│   ├── opcode.h
│   ├── program.h
│   └── assembler.h
│
├── src/
│   ├── main.c
│   ├── lexer.c
│   ├── token.c
│   ├── parser.c
│   ├── program.c
│   ├── instruction.c
│   ├── opcode.c
│   ├── assembler.c
│   └── IO/
│       ├── read_file.c
│       └── write_file.c
│
├── tests/
│   ├── test_token.c
│   ├── test_lexer.c
│   ├── test_parser.c
│   ├── test_opcode.c
│   └── test_assembler.c
│
├── Makefile
└── README.md
```

---

# Supported Syntax

Current examples:

```asm
MOV r1, r2

ADD r3, 5

JMP loop
```

Supported operands:

```
r1-r8       Registers

number      Immediate values

label       Labels
```

---

# Example Conversion

Input:

```asm
MOV r1, r2
ADD r3, 5
```

Internal representation:

```
Instruction 1:

MOV
REGISTER r1
REGISTER r2


Instruction 2:

ADD
REGISTER r3
IMMEDIATE 5
```

Output:

```
01 01 02
02 03 05
```

---

# Current Limitations

This assembler is still educational and does not yet support:

* Real CPU instruction encoding
* ELF/PE executable formats
* Label resolution
* Symbol tables
* Multiple assembly passes
* Memory addressing
* Comments
* Macros
* Variables
* Debug information

---

# Future Roadmap

Next improvements:

1. Add symbol tables for labels
2. Implement two-pass assembly
3. Resolve jump addresses
4. Add memory operands
5. Expand instruction set
6. Implement a virtual machine to execute generated machine code
7. Add a debugger for the virtual machine

---

# What This Project Teaches

This project demonstrates the core ideas behind assemblers:

```
Assembly language

        |

        v

File reading

        |

        v

Lexical analysis

        |

        v

Parsing

        |

        v

Intermediate representation

        |

        v

Code generation

        |

        v

Binary machine code
```

The project is built step by step to understand how real compiler and assembler tools are designed.

```
```

