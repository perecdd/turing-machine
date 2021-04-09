# turing-machine

An abstract calculator that allows you to process an input string of data using a user-written program. To see detailed information about this machine [click on the link](thiswikipedia.org/wiki/Turing_machine

The machine requires the input of the full name of the file, which will record the possible states, the alphabet, the program of the machine, the initial state, the final state. Write it down in the following form:
1. States separated by a space
2. Alphabet separated by a space
3. Start and end state separated by a space
4. A program separated by a semicolon

Example:
<br>q0 q1 q2 q3 q4
<br>0 1 E
<br>q0 q4
<br>q0, 0 -> q1, 0, 1;
<br>q0, 1 -> q1, 1, 1;

After creating and entering the file, you need to type a word consisting of the characters of the language you entered:
<br>Σ = {0, 1, E}
<br>Example:
<br>00010111EE111

More examples can be found in the corresponding folder.

You can find the source code for self-compilation in "Source code".