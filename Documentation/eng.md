# Turing Machine

An abstract calculator that allows you to process an input string of data using a user-written program. To see more information about this machine [click on the link](thiswikipedia.org/wiki/Turing_machine)

## What you need it for

According to [the Church — Turing thesis](https://ru.wikipedia.org/wiki/Thesis_church_—_Turing), *is capable of simulating all performers* who somehow implement the step-by-step calculation process, in which each step of the calculation is quite elementary. That is, any intuitive algorithm can be implemented with the help of some Turing machine.

## Basic terms

A Turing machine can be formally defined as M = {Q, A, b, Σ, q0, F, ẟ}

Q is a finite and non-empty set of states that the program can go to.

A - Alphabet; A finite and non-empty set that contains all possible characters of the input tape.

b - Empty character,

Σ - Possible input characters (All alphabet characters except b).

q<sub>0</sub> - Initial state

F - The final or receiving states of the program. If the initial content of the tape stops in one of the final states, it is said that it is accepted by the program.

ẟ - Transition function, L-left, left movement, R-right, right movement.

This device is a deterministic Turing machine, i.e. for each combination of state and symbol, there is only one transition rule.

## Instructions

Input to the machine is carried out by a text file. To do this, enter the full name of the file with the extension in the first line.

M = {Q, A, b, Σ, q0, F, ẟ}. The file is filled in as follows:

1. Q. States separated by a space.
2. A. All possible characters, the placement of spaces between them-as desired.
3. b. One "empty" character.
4. Σ - No need to do anything, it is determined automatically.
5. q0 - Name of the start state
6. F - Receiving states. F⊆Q
7. ẟ-Specified in the commands: shift to the right - +1, shift to the left--1, no movement - 0.
8. Program commands separated by semicolons in the format: state, character - > state, character, transition; (q0, 0 - > q1, 1, +1;)

Examples can be found in the "Examples" folder.

After the above steps, you need to run the program and enter the word to be processed.