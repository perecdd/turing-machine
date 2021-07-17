# The Turing machine
A Turing machine is an abstract computing machine that manipulates symbols on a strip of tape according to a table of rules. Despite the simplicity of the model, according to the Church-Turing thesis, a Turing machine can be built for any computer algorithm that can simulate the logic of this algorithm.
The rules table is set using commands that have the following form:
"q, a - > p, b, r;", where q, p are the states of the Turing machine, a, b are the symbols of the alphabet, r is the direction of the machine head shift. The states and the alphabet are set by the user when writing the program.
If there is no command for the next symbol on the tape and this state, the program ends.

The tape is a set of cells in which characters are stored. According to them, the machine can walk in both directions one cell at a time. The peculiarity of this implementation is that the tape can have arbitrary sizes and increase in the course of work. Only lines where the characters are not a combination of other characters can be entered. Simply put, {b, a, &, ^, (, ...} - suitable characters, and {b*, a^, r^,...} are combined characters, they cannot be used as input, however, during operation, the program can change single-character characters to combined characters and, eventually, the program will be able to output them.

You can find examples of programs and tapes in the "Examples" folder.

# How to use

Before using the Turing machine, you need to perform the following steps:
## Write a program
You need to create a file with the program and write it there. The main thing is that there should be only one command on each line: For
example, q0 is the state, {0, 1} is the alphabet, +1 is the shift.
The states and the alphabet can consist of any number of characters.
The shift must necessarily be an integer belonging to [-1;1].
The following reserved characters cannot be used in commands:, - > # ;
Example of a simple program:
~~~
q0, 0 - > q0, 1, +1;
q0, 1 -> q0, 0, +1;
~~~
This program will replace all 1's with 0's, and all 0's with 1's.

There can be any number of whitespace characters between states and symbols, including zero. Example of a valid program
~~~
q0,0->q0,1,+1;
q0,   1   ->   q0,   0,   +1;
~~~

In order to add a comment to a line, you need to add the '#'symbol before it:
~~~
q0, 0 -> q0, 1, +1; # This line of code changes 0 to 1.
q0, 0 -> q0, 1, +1;
# And this line of code changes 1 to 0.
~~~
Comments should be placed after the '# ' character. You can use any symbols behind this symbol.
There may be empty lines in the program file, they will be ignored, however, if you decide to write comments, you will also need to add the '# ' character first.

## Create a feed
The program for the Turing machine accepts a tape with symbols as input. You need to create this feed.
You need to create a separate file in which each line is a separate tape. Watch out for empty lines, the program will work with them as with empty tapes.
For example, for the previous program, you can create the following file with tapes:
~~~
001
101
000
~~~

The result will be written to log.txt:
~~~
Input:001
001
^
101
^
111
^
110^
^
Output:110^

Input:101
101
^
001
^
011
^
010^
^
Output:010^

Input:000
000
^
100
^
110
^
111^
^
Output:111^
~~~
The '^' character simultaneously denotes an empty character and is a pointer to the tape character that is currently being read.

## Starting the program
When the program is written and the input data is prepared, you need to run the program and follow the instructions: enter the name of the program file (the path, if necessary, in the format "C:\MyFiles\...\Input.txt"), press Enter, also enter the name of the data file, enter the name of the state from which your program should start working.
If the program has worked successfully, the message "The program has successfully completed its work" will be displayed in the console, the result will be written to log.txt.
If an error was issued, then you will need to fix it to continue working.
