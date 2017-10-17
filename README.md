# Evaluator
No piece of software can be proven to work before being evaluated. I wrote this program before taking my first CS class at UC Davis as a pre-emptive method of testing my code against a set of input and output files. It uses unix syscalls to manage a child process that executes the executable under consideration and compares its stdout to a file, stopping when it finds differences.

This method became obsolete after using gradescope and Sean's testhw, and functionally it combines the two steps of running a program and running diff on top of it, but it does correctly implement POSIX methods for forking, piping stdin/out file descriptors, and executing other code. Unlike a shell script it isn't dependent on the shell environment it runs on. That's about it. 

Install
========
run `mkdir build && cd build && cmake ../src && make`

Usage
======
`evaluate <program> <input_file> <output_file> [arguments passed to program]`
