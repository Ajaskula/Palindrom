Palindrom (Connect Four) Game
This project involves creating a program that allows two players to play the Palindrom game, a variant of the well-known Connect Four game.

Introduction
The Palindrom game is played by two players, referred to as "First" and "Second," on a vertically oriented rectangular board divided into rows and columns. Each player has their own type of pawn.

At the beginning of the game, the board is empty, and the First player makes the first move.

Players take turns placing their pawns on the board. The pawn is placed in the selected column, in the first available cell from the bottom of that column.

A player wins if they create a palindrom of a specified length by placing pawns on consecutive cells in the same row, column, or diagonal.

Parameters
The game is parameterized by three positive integers:

ROWS: the number of rows on the board.
COLUMNS: the number of columns on the board.
LENGTH: the length of the palindrom to be created.
These parameters are defined as symbolic constants that can be specified using the compiler's -D option. Default values for these constants are provided as follows:

ROWS is set to 8.
COLUMNS is set to 8.
LENGTH is set to 5.
Game Execution
The program, in a loop:

Displays the current state of the board and indicates which player is to make a move.
Reads the player's command.
If the command is a valid move, executes it.
If the command is to end the game, terminates the program.
The loop ends when:

The program receives the command to end the game, or
One of the players wins.
If one of the players wins, the program will display the final state of the board and announce the winner.

Input Format
The input to the program consists of commands from the players. Each command occupies one line. All commands are valid. After the last command, there can be any text, which will be ignored by the program.

In a move command, the player specifies the column where they want to place their pawn. Columns are named with consecutive lowercase letters, starting from 'a'.

A move command is valid if the specified column has an available cell for the pawn.

The command to end the game consists of a single dot character '.'

Output Format
The program's output consists of a sequence of board diagrams. After each diagram, there is a line indicating which player is to make a move or who won the game.

The board diagram describes each cell using the following characters:

A space character when the cell is empty.
'1' when the cell contains the pawn of the First player.
'2' when the cell contains the pawn of the Second player.
The cells' descriptions are grouped in rows, ordered from the highest to the lowest row. The cells in each row are ordered based on the columns, starting from column 'a'.

After the last row of cells in the diagram, there is a row with the names of the columns. Each column name is preceded by a space.

The information about which player is to make a move has the format of a line with the player's name, '1' or '2', followed by a colon.

The information about who won the game has the format of a line with the player's name, '1' or '2', followed by an exclamation mark.

There are no characters in the output text that have not been mentioned above.

Each printed line, including the last one, ends with the end-of-line character '\n'.

In files there are examples compiled with the command:

gcc @opcje -DWIERSZE=8 -DKOLUMNY=8 -DDLUGOSC=5 zadanie1.c -o zadanie1
Input data files with example commands are provided as .in files, and the expected output for each example is provided as .out files.

For the input data in the file przyklad1.in, the correct output is in przyklad1.out.
For the input data in the file przyklad2.in, the correct output is in przyklad2.out.
For the input data in the file przyklad3.in, the correct output is in przyklad3.out.
