# Interactive-ARM-Trainer-and-Morse-Encoder
A project extension to Imperial College's ARM Project

```
ARM Project
Group 18: Giulio Jiang, Ivan Procaccini, Feroz Jilla, Elias Benussi
@ Imperial College London, Department of Computing
2015

The final first year project at Imperial College consists in the development
of an ARM emulator and assembler.
This repository contains the extension me and my group have
enriched the project with. There are two programs: the 
Interactive ARM Trainer and the Morse Encoder.

The Interactive ARM Trainer is a collection of mini-games based
on the ARM assembly language. Through them the user should learn how to
use some of the main instructions together with a few useful programming tricks.
There is also a simple ARM interpreter in which it's possible to
directly write ARM programs.

The Morse Encoder is a program that, given a string, returns the
assembly code reproducing its Morse codification; the assembly code in turn is such that, when run
on the Raspberry Pi, it make the green LED on the board flash the correct sequence
of "dashes and dots". To achieve this, the kernel.img file produced by the program can be used
on a Raspberry Pi by replacing the kernel.img of the operating system.

In the root directory there are scripts to compile and run the
GUI launchers. Both programs have been tested on Linux machines, but
are not yet compatible with other systems.

The GUI launchers require Java 7 or above. 
Otherwise, command line versions can also be called directly.

The executables are
src/assemble
src/emulate
src/IAT/interpreter
src/IAT/trainer_branch
src/IAT/trainer_dp
programs/morse/MorseEncoder

Unfortunately we cannot release the source code for emulator and
assembler as this would not be fair for future first year students of our Dept.
However, should you be interested in our implementation choices, feel free
to ask questions.

All the files in this repository are released under
Apache License 2.0
```
