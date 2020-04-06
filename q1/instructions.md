Q1 - Microcontroller tools
==========================

Overview
========

The MU0 Instruction Set Architecture
------------------------------------

The MU0 instruction set describes a processor with:

- 4096 16-bit memory locations.
- 16-bit instructions
- A single 16-bit accumulator register called `ACC`.
- A single 12-bit program counter called `PC`.


Each instruction consists of a 4-bit op-code,
plus a 12-bit operand-address. The instruction
op-codes defined for MU0 are:

| Dec | Bin  | ASM   | Operation                                 |
|-----|------|-------|-------------------------------------------|
| 0   | 0000 | LDA S | ACC = memory[S]                           |
| 1   | 0001 | STA S | memory[S] = ACC                           |
| 2   | 0010 | ADD S | ACC = ACC + memory[S]                     |
| 3   | 0011 | SUB S | ACC = ACC - memory[S]                     |
| 4   | 0100 | JMP S | PC = S                                    |
| 5   | 0101 | JGE S | if ACC >= 0 then PC = S                   |
| 6   | 0110 | JNE S | if ACC != 0 then PC = S                   |
| 7   | 0111 | STP   | halt the program                          |
| 8   | 1000 | INP   | ACC=mu0_input()                           |
| 9   | 1001 | OUT   | mu0_output(ACC)                           |

Unless otherwise specified, the PC always advances by 1.

Program execution always starts at address 0.

Valid programs must not cause the PC to wrap-around (it must always
stay in `[0,4095)`).

The accumulator always has the initial value 0.

Any arithmetic operations on data words should treat values
as 16-bit twos-complement data.

Note that this definition is an extension of the standard MU0 due
to the addition of the `INP` and `OUT` instructions. These instructions
rely on the functions `mu0_read` and `mu0_write` defined in
`mu0_simulator_io.hpp`.

Assembly encoding
-----------------

MU0 assembly programs are represented as a sequence of white-space
separated values, which are then interpreted as a sequence of
instructions, data, and labels:

- **Instructions**: an instruction consists of one or two values.
  The first value is the instruction name. Instructions which
  have a memory operand will also have a second value, which is
  either:

  - A decimal integer giving an absolute address; or
  - A _label name_.

- **Data**: data values consist of signed decimal integers.

- **Label declaration**: a label declaration is a _label name_,
  immediately followed by a colon (`:`). 

The rules for valid label names are the same as those for C++ identifiers:

1. Starts with an alphabetic character or `_`.
2. Followed by zero or more alpha-numeric characters or `_`.

- Examples of valid labels include `X:`, `ggg:`, `y23:`, and `xXx:`.
- Examples of non-labels include `X :`, `ggg`, `123y:`, and `x0:`.

The rules for valid absolute addresses and data values are the same
as for decimal integer constants used with `cin >> i`: an optional
sign, followed by zero or more decimal digits.

Octal and hexadecimal numbers are not allowed anywhere in the assembly.

All data constants must be in range for a 16-bit twos complement number.

All absolute addresses must be in range `[0,4096)`.

Instructions and data are laid out at sequential locations in
memory, starting at address 0.

Label declarations establish that the label name refers to the
address of the next instruction or data that follows them.

Assembly code is case-sensitive throughout.

Programs reading assembly should assume the input assembly is valid,
and are **not** required to check for input errors such as invalid
constants, out of range addresses, or missing labels.

Binary encoding
---------------

Binary programs are represented as files
containing hexadecimal characters:
- Either lower or upper-case hex-digits can be used.
- Each line contains exactly 4 characters.
- The most significant digit appears first on the line.
- Instructions with no memory operand contains zeros in the least-significant 12 bits.
- Binary programs consist of up to 4096 16-bit words. If there are less than
  4096 words, the remainder will be assumed to be zero.

Examples
--------

If we have the assembly:
```
STA 1234
```
The equivalent binary would be:
```
14d2
```

The following assembly contains four labels:
```
   LDA TEN
Z: OUT
   ADD NEG_ONE
   JNE Z
Y: STP
TEN: 10
NEG_ONE: -1
```
The addresses of those labels are:
- `Z`   : 1
- `Y`   : 4
- `TEN` : 5
- `NEG_ONE` : 6

In binary, the program is:
```
0005 
9000
2006
6001
7000
000A
FFFF
```

Executing this program would produce the output:
```
10
9
8
7
6
5
4
3
2
1
```

Tasks
=====

T1 - Encoding assembly to binary (40%)
--------------------------------------

### T1.1 - Implement the `mu0_is_label_decl` function

Complete the definition of `mu0_is_label_decl` so that
it can tell whether the input string is a valid label
declaration.

### T1.2 - Implement the `mu0_is_data` function

Complete the definition of `mu0_is_data` so that
it can tell whether the input string is valid numeric
data.

### T1.3 - Overload the `mu0_is_instruction` function

Create an overload for `mu0_is_instruction` which takes a string
argument, and returns true if and only if the argument is
a valid three-letter op-code.

The overload should be declared in `mu0.hpp`, and defined
in `mu0_assembly.cpp`.

### T1.4 - Create a program to list label names

Create a program `list_labels.cpp` which reads assembly code
from `stdin`, and prints a list of label names occurring in the
assembly to `stdout`.

You should also include a script `build_list_labels.sh` which
will compile `list_labels.cpp` into a program `list_labels`.

Each output label should appear on a different line, and
should **not** include the colon (`:`).

The labels should be sorted lexicographically from smallest
to largest (this is the standard sort order for `string`).

For the program given earlier, the output would be:
```
NEG_ONE
TEN
Y
Z
```


### T1.5 - Create a program to assemble programs to binary

Create a program `assembler.cpp` which reads assembly code
from `stdin`, and prints equivalent binary to `stdout`.

You should include a script `build_assembler.sh` which
will compile `assembler.cpp` into a program `assembler`.

Two levels of functionality are recognised:

- **Absolute** : The assembler is able to process assembly files
  that do not contain labels, and only uses absolute addresses.

- **Labelled**: The assembler is also able to correctly process
  and resolve labels.


T2 - Decoding binary to assembly  (30%)
---------------------------------------

### T2.1 - Implement the function `mu0_disassemble_instruction`

Complete the implementation of `mu0_disassemble_instruction` so that
it produces a `string` containing the disassembled instruction. A
disassembled instruction is either:

- The three-letter upper-case opcode, followed by a space and a
  decimal integer if the opcode has an operand; or

- A decimal integer, if the instruction does not describe a valid op-code.

The output of `mu0_disassemble_instruction` should represent a valid
instruction or data constant that could appear in an assembly file.

Some examples of disassembly are:

| Constant   | Disassembly |
|------------|-------------|
| `0x0000`   | `LDA 0`     |
| `0x2123`   | `ADD 291`   |
| `0x7999`   | `STP`       |
| `0x9000`   | `-28672`    |
| `0xFFFF`   | `-1`        |

### T2.2 - Create a program to disassemble binary to assembly

Create a program `disassembler.cpp` which reads a binary from
`stdin`, and prints equivalent disassembly to `stdout`.

You should include a file called `build_disassembler.sh` which
will build `disassembler.cpp` into a program `disassembler`.

You can assume that all binaries are _consistent_.

Two levels of functionality are recognised:

- **Absolute**: each 16-bit word in the binary is converted to an
  individual instruction in isolation.

- **Labelled**: all address operands are printed as labels.
  Any label names can be used, as long as they would result in
  the same binary when assembled.

### T2.3 - Create a test script for binary -> assembly -> binary

Create a script called `test_round_trip.sh` which:

1 - Uses the disassembler to produce assembler for one or more test binaries.
2 - Uses the assembler to produce binaries from the assembler.
3 - Checks that the input and output binaries are equivalent.

The script should print `Success` if and only if all binaries
are equivalent.

It can be assumed that the `assembler` and `disassembler` binaries have
already been built using `build_assembler.sh` and `build_disassembler.sh`,
though your test script can re-compile them if you wish.

Your script may compile any other programs needed to perform the test.

_Note that this script can (and should) test for features you have_
_not implemented. You can assume that it will be tested on assemblers_
_and disassemblers that you did not write, which will include_
_both correct and incorrect implementations._

_Note that binary files have special provision for omitting trailing zero words._

T3 - MU0 simulator  (30%)
-------------------------

The source file `simulator.cpp` provides a main
file which can drive the `mu0_simulator` function. This program
reads a MU0 binary from stdin, and then uses the `mu0_simulator`
function to simulate it. The script `build_simulator.sh` will
compile the sources files into a program `simulator`.

### T3.1 Implement mu0_simulator

Implement the function `mu0_simulator` in `mu0_simulator_core.cpp`.

- The function receives a pointer to 4096 words
  representing the memory contents, and should execute
  the program.
- The function should return when the `STP` instruction is executed.
- The return value should be the final value of `ACC`.
- The function should not read `stdin` or write `stdout`, except
  via `mu0_input`, and `mu0_output`.
- The memory contents should be modified in place, which means
  that when the function returns the array should represent
  the final state of the CPU's memory.

### TT3.2 Create a simulator testbench

Create a test script called `test_simulator.sh` which will
use at least one test-case to check whether the `simulator`
binary works.

The script should print `Success` if and only if the simulator
passes all tests.

It can be assumed that `simulator` has already been compiled via
`build_simulator.sh`, but your script can recompile if you wish.
