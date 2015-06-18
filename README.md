# Interactive-ARM-Trainer-and-Morse-Encoder
A project extension to Imperial College's ARM Project

```
ARM Project
Group 18: Giulio Jiang, Ivan Procaccini, Feroz Jilla, Elias Benussi
@ Imperial College London
2015

The final first year project at Imperial College consists in the developing
of an ARM emulator and assembler.
This repository contains the extension that me and my group have
developed to the project. There are two programs: the 
Interactive ARM Trainer and the Morse Encoder.

The Interactive ARM Trainer is a collection of mini-games based
on the ARM assembly language. They will try to teach the user how to
use some of the instructions, and a few useful programming tricks.
There is also a simple ARM interpreter in which it's possible to
directly write ARM programs.

The Morse Encoder is a program that given a string will return the
assembly code to reproduce the Morse sequence using the green LED
on the Raspberry Pi board. The produced kernel.img file can be used
on a Raspberry Pi by replacing the kernel.img of the operating system.

In the root directory there are scripts to compile and run the
graphical launchers. All programs have been tested on Linux machines, but
are not compatible with other systems at the moment.

The graphical launchers require java7 or above. Otherwise, command line
versions can also be called directly.

The executables are
src/assemble
src/emulate
src/IAT/interpreter
src/IAT/trainer_branch
src/IAT/trainer_dp
programs/morse/MorseEncoder

Unfortunately we cannot release the source code for emulator and
assembler as this would not be fair for the future students of our course.
However, if you are interested in our implementation choices, feel free
to ask questions.
```
