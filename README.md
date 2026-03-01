# seekview
A small Unix-style utility written in C that demonstrates file offset
manipulation using the POSIX lseek system call.
This project was developed while studying *Advanced Programming in the UNIX Environment (APUE)*

## Overview

`seekview` opens a file, moves the file offset using `lseek`,
and prints the remaining contents to standard output

## Usage
./seekview <file> <offset> <whence>

