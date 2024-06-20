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
