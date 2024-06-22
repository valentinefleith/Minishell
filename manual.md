# Bash Manual

## Introduction 

### What is shell ?

Unix shell = both **command interpreter** and **programming language**. Can be used **interactively** (input) or non-interactively (from file) (for minishell -> interactive shell).

Shell allows **executing commands** : GNU commands and built-in commands (_builtins_). Built-in commands cannot be implemented outside of the shell because they directly manipulate the shell itself. For example : `cd`, `break`, `exec` etc. Others like `pwd` could be implemented in separate utilities but they are more convenient as builtin. 

Also interactive features such as : job control, command line editing, command history and aliases.

### Useful definitions

**`POSIX`**: family of open system standards based on Unix.

**`builtin`**: a command that is implemented internally by the shell itself rather than by an executable program somewhere in the file system.

**`control operator`**: a `token` that performs a control function (`||`, `&&`, `|`, `;`, etc.).

**`exit status`**: value returned by a command to its caller. The value is restricted to eight bits so the maximum value is 255. Synonym = `return status`.

**`job`**: a set of processes comprising a pipeline, and any processes descended from it, that are all in the same process group.

**`job control`**: a mechanism by which users can selectively stop (suspend) and restart (resume) execution of processes.

**`token`**: a sequence of characters considered as a single unit by the shell, it is either a word or an operator.

## Basic shell features

### Shell syntax
- **single quotes**: enclosing characters in single quotes preserves value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash.
- **double quotes**: enclosing characters in double quotes preserves the literal values of all characters within the quotes, with the exception of `$`,\`,`\\` and `!`. A double quote may be quoted within double quotes by preceding it with a backslash. The special parameters `*` and `@` have special meanings

### Shell commands

A `pipeline` is a sequence of one or more commands separated by one of the control operators (only `|` for our project).

A `list` is a sequence of one or more pipelines separated by one of the operators `;` `&`, `&&` or `||`. -> not necessary for our project??

Note that wherever a `;` appears in the description of a command's syntax, it may be replaced with one or more newlines.

### Shell parameters

A _parameter_ is an entity that stores values. It can be a `name`, a number or one of the special characters listed below. 

A _variable_ is a prameter denoted by a `name`. A variable has a `value` and and zero or more attributes. A variable may be assigned to by a statement of the form:
```
name=[value]
```

If `value` is not given, the variable is assigned to null string. 

In the context where an assignment statement is assigning a value to a shell variable or array index, the `+=` operator can be used to append to or add the variable's previous value. Then the variable's value is not unset (as it is when using `=`).

**Special parameters**:

- `$*` (positional parameters starting from 1)
- `$@` (positional parameters, starting from 1)
- `$#` number of positional parameters in decimal
- `$-` the current option flags 
- `$$` the process ID of the shell.
- `$!` the process ID of the job most recently placed into the background
- `$0` the name of the shell or shell script

### Redirections

Before a command is executed, its input and output may be _redirected_ using a special notation interpreted by the shell. Note that the order or redirection is significant. 

- `/dev/stdin` -> file descriptor 0 is duplicated
- `/dev/stdout` -> file descriptor 1 is duplicated
- `/dev/stderr` -> file descriptor 2 is duplicated

__Redirecting input__ : causes the file whose name results from the expansion of _word_ to be opened or reading on file descriptor _n_, or the stdin if n is not specified.
```
[n] < word
```

__Redirecting output__ : causes the file whose name results from the expansion of _word_ to be opened for writing on file descriptor _n_ or stdout if n is not specified. If the file does not exist it is created.
```
[n] > word
```

__Appending redirected output__ : causes the file to be opened for appending on file descriptor n or stdout if n not specified.  If the file does not exist it is created. 
```
[n] >> word
```

__Here documents__ : instructs the shell to read input from the current source until a line containing only word is seen. All the lines are then used as input for a command.

```
[n]<<word
    here-document
delimiter
```

### Executing commands

The following actions are taken:
1. If the command name contains no slashes, the shell attempts to locate it. If there exists a shell function by that name, that function is invoked.
2. If the name does not match a function, the shell searched for it in the list of shell builtins. If a match is found, that builtin is invoked.
3. If the name is neither a shell function nor a builtin, and contains no slashes, bash searches each element of `$PATH` for a directory containing an executable file by that name. If that function is not defined, the shell prints an error message and returns an exit status of 127.
4. If the search is successfull, or if the command name contains one or more slashes, the shell executes the named program.

**Exit status:**
The exit status of an executed command is the value returned by the `waitpid` system call. Exit statuses fall between 0 and 255 but the shell may use values above 125 specially. 

- a command which exits with a zero exit status has succeeded / non zero status indicates falure. **When a command terminates on a fatal signal whose number is N, Bash uses the value 128+N as the exit status.**
- if a command is not found, the child process created to execute it returns a status of 127.
- if a command is found but is not executable, the return status is 126.
- if a command fails because of an error during expansion or redirection, the exit status is greater than 0.
- all builtins return an exit status of 2 to indicate incorrect usage, generally invalid options or missing arguments.
- the exit status of the last command is available in the special parameter `$?`.

**Signals** :
When job control is not enabled, and Bash is waiting for a foreground command to complete, the shell receives keyboard-generated signals such as `SIGINT` (usually generated by `^C`) that users commonly intend to send to that command. This happens because the shell and the command are in the same process group as the terminal, and `^C` sends `SIGINT` to all processes in that process group. 

