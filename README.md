# Zetavblitz/sprinter

CLI tool for tracking wordcount progress with a timer.

## Setup

For unix systems, clone the repository to local. The included binary is compiled for x86 linux. Alternatively, with just the source file `sprinter.c`, you can run `gcc -O3 sprinter.c -o sprinter` to compile yourself.

Support for non-unix systems is not available yet.

## Use

Simply run the program `./sprinter` from the commandline in the directory where it is located. The default sprint duration without optional arguments is 15 minutes. You can instead set a custom duration by specificing a positive, integer number after the program name.

The program will ask you for a starting wordcount. Upon input, the timer will begin running for the given duration. While the sprint is running, there are several commands you can use:

- `cancel` : cancels the sprint and terminates program execution.
- `pause` : pauses the timer.
- `resume` : resumes a paused timer.
- `time` : displays the time remaining to the nearest minute.

When the timer finishes, input your final wordcount. You will then see the total change along with a calculated wpm (words per minute).
