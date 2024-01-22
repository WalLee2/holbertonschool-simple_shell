# holbertonschool-simple_shell

Refactoring the original [simple shell](https://github.com/WalLee2/simple_shell) project into more modular and testable pieces.

##### Holberton Shell (hsh) is a simple command line shell that will execute commands found in the PATH. Commands like ```ls``` and ```grep``` will execute.

## Getting Started

To use hsh, you can give it commands. hsh commands follow the following syntax: `command {arguments}`.

### Commands

The below is an incomplete list of commands that can run. The commands with their respective flags will also run properly as well.

```
cat
chmod
cp
grep
ls
pwd
ps
mv
rm
```

### Execution examples
```
$ /bin/ls -la
input_output.c  main.c  memory.c  README.md  shell.h  strings.c  test_shell  hsh
$ /usr/bin/ls -la
total 80
drwxrwx--- 1 root vboxsf   352 Jan 22 13:49 .
drwxrwx--- 1 root vboxsf   288 Jan 21 18:14 ..
drwxrwx--- 1 root vboxsf   416 Jan 22  2024 .git
-rwxrwx--- 1 root vboxsf  1995 Jan 22  2024 README.md
-rwxrwx--- 1 root vboxsf 22464 Jan 22 13:49 hsh
-rwxrwx--- 1 root vboxsf  1388 Jan 21 18:45 input_output.c
-rwxrwx--- 1 root vboxsf  3856 Jan 21 18:45 main.c
-rwxrwx--- 1 root vboxsf  2596 Jan 21 18:46 memory.c
-rwxrwx--- 1 root vboxsf  2342 Jan 21 18:28 shell.h
-rwxrwx--- 1 root vboxsf  8647 Jan 21 18:49 strings.c
-rwxrwx--- 1 root vboxsf 22464 Jan 21 17:31 test_shell
```
```
$ ls
input_output.c  main.c  memory.c  README.md  shell.h  strings.c  test_shell  hsh
$ ls -la
total 80
drwxrwx--- 1 root vboxsf   352 Jan 22 13:49 .
drwxrwx--- 1 root vboxsf   288 Jan 21 18:14 ..
drwxrwx--- 1 root vboxsf   416 Jan 22  2024 .git
-rwxrwx--- 1 root vboxsf  1995 Jan 22  2024 README.md
-rwxrwx--- 1 root vboxsf 22464 Jan 22 13:49 hsh
-rwxrwx--- 1 root vboxsf  1388 Jan 21 18:45 input_output.c
-rwxrwx--- 1 root vboxsf  3856 Jan 21 18:45 main.c
-rwxrwx--- 1 root vboxsf  2596 Jan 21 18:46 memory.c
-rwxrwx--- 1 root vboxsf  2342 Jan 21 18:28 shell.h
-rwxrwx--- 1 root vboxsf  8647 Jan 21 18:49 strings.c
-rwxrwx--- 1 root vboxsf 22464 Jan 21 17:31 test_shell
```

## Installation

Clone the repository:

```
git clone https://github.com/WalLee2/holbertonschool-simple_shell.git
```
or
```
git clone git@github.com:WalLee2/holbertonschool-simple_shell.git
```

Compile:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## File Description
[shell.h](shell.h) - Header file: struct definitions, macros, function prototypes and standard libraries included.<br>
[main.c](main.c) - The main function gives a high level overview of how the shell runs. All functions below main contain operation details.<br>
[input_output.c](input_output.c) - Contains all functions that are needed for input and output like ```_getline```.<br>
[memory.c](memory.c) - Contains all functions that requests or frees memory.<br>
[strings.c](strings.c) - Contains all functions that manipulate strings which includes token generation from user inputs and string character filtering.<br>


## Built With

* [The C Programming Language](https://en.wikipedia.org/wiki/The_C_Programming_Language)


## Acknowledgments

* Thank you to <a href="https://www.holbertonschool.com/">Holberton School</a>
