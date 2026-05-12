# Simple Assembler (Educational Project)

This project is a very small educational assembler written in C.

It converts simple assembly-like instructions into hex machine-code-like output.

It is NOT a real assembler yet — it is an incremental learning project that demonstrates how assemblers are built step by step.

---

# What this project does

- Reads an assembly file line by line
- Parses instruction, register, and immediate value using `sscanf`
- Uses lookup tables to map mnemonics → opcodes and registers → codes
- Encodes instructions into a simple 3-byte format
- Outputs results to both console and file (`bin.hex`)

---

# Supported syntax

Only this exact format is supported:

ADD eax, 2  
SUB ebx, 5  
MOV ecx, 10  

Rules:
- One instruction per line
- Must include register + immediate value
- Comma is required between register and number
- No extra syntax supported

---

# How it works (pipeline)

Assembly file  
→ read line  
→ parse with sscanf  
→ lookup opcode  
→ lookup register code  
→ emit encoded bytes  

---

# Instruction set

ADD → 0x83  
SUB → 0x81  
MOV → 0xB8  

---

# Register set

eax → 0  
ebx → 1  
ecx → 2  
edx → 3  

---

# Output format

Each instruction becomes:

opcode + register_code + immediate_value

Example:
ADD eax, 2 → 83 00 02  

---

# Example input file (program.asm)

ADD eax, 2  
SUB ebx, 5  
MOV ecx, 10  

---

# Build

gcc main.c -o assembler  

---

# Run

./assembler program.asm  

---

# Output example

Console:
ADD eax, 2 → 83 00 02  
SUB ebx, 5 → 81 01 05  
MOV ecx, 10 → B8 02 0A  

File (bin.hex):
83 00 02  
81 01 05  
B8 02 0A  

---

# How parsing works

The program uses:

sscanf(source, "%s %[^,], %d", instruction, reg, &value)

This extracts:
- instruction → "ADD"
- register → "eax"
- value → 2

---

# Encoding logic

Final format is fixed:

opcode (1 byte)  
register code (1 byte)  
immediate value (1 byte)

---

# ⚠️ Limitations (IMPORTANT)

This is a highly simplified educational assembler. It has many limitations:

## 1. Extremely strict input format
- Must match exact syntax: `INSTR reg, number`
- No flexibility in spacing or formatting
- Missing comma or extra spaces can break parsing

## 2. Only immediate + register form
- No memory addressing (`[eax]`, `[ebx+4]`, etc.)
- No register-to-register operations
- No instruction variants (like real CPU encodings)

## 3. Very limited instruction set
- Only ADD, SUB, MOV
- No arithmetic variants (IMUL, DIV, INC, DEC, etc.)
- No control flow instructions (JMP, CALL, RET)

## 4. No labels or symbols
- Cannot use labels like:
  start:
  loop:
- No jumps or branching support
- No symbol resolution

## 5. No real machine code format
- Output is plain hex text, not binary executable format
- No ELF, PE, or raw binary generation

## 6. Weak parsing system
- Uses `sscanf`, which is fragile
- Cannot handle:
  - multiple spaces
  - tabs reliably
  - comments
  - malformed input gracefully

## 7. No error handling system
- Unknown instructions silently return 0
- Invalid registers map to 0xFF
- No meaningful assembler error messages

## 8. Fixed-size assumptions
- Only supports small integer immediates
- No 16/32/64-bit instruction handling
- No overflow checks

---

# What this project teaches

This project demonstrates the core idea of assemblers:

Assembly code  
→ structured parsing  
→ opcode lookup  
→ numeric encoding  

It is the foundation of real compiler and assembler design.

---

# Next steps (recommended evolution path)

1. Replace `sscanf` with a real character-based tokenizer  
2. Add token types (INSTR, REG, IMM)  
3. Introduce labels and symbol table  
4. Implement multi-pass assembly  
5. Output real binary format instead of hex text  
6. Expand instruction encoding system  
