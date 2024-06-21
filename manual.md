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
- **double quotes**: enclosing characters in double quotes preserves the literal values of all characters within the quotes, with the exception of `$`,`\``,`\\` and `!`. A double quote may be quoted within double quotes by preceding it with a backslash. The special parameters `*` and `@` have special meanings

### Shell commands

A `pipeline` is a sequence of one or more commands separated by one of the control operators (only `|` for our project).

A `list` is a sequence of one or more pipelines separated by one of the operators `;` `&`, `&&` or `||`. -> not necessary for our project??
