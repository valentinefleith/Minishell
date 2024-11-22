![img](assets/compilation.gif)


# Minishell

Minishell is a **command-line interpreter** designed to mimic bash's behavior. It is built from scratch using C.

Parsing architecture relies on an **Abstract Syntax Tree (AST)** and **shift-reduce parsing algorithm**.

## Features

### Command execution:

- Display a **prompt** when waiting for a new command.
- Have a working **history**.
- Search and launch the right executable (based on the `PATH` variable or using a
relative or an absolute path).
- Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
- Support custom **built-in commands**:
    - `cd` with no options
    - `pwd` with no options
    - `echo` with option `-n`
    - `export` with no options
    - `unset` with no options
    - `env` with no options or arguments
    - `exit` with no options

### Operators

- Implement **pipes** (`|` character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- Implement **redirections**:
    - `<` should redirect **input**.
    - `>` should redirect **output**.
    - `<<` should implement **heredocs**. It should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
    - `>>` should redirect output in **append mode**.

### Shell-specific behaviors

- Handle **environment variables** ($ followed by a sequence of characters) which
should **expand** to their values.
- Handle `$?` which should expand to the **exit status** of the most recently executed
foreground pipeline.
- Handle `’` **(single quote)** which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
- Handle `"` **(double quote)** which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for `$` (dollar sign).
- **Signal Handling:** Handle `ctrl-C`, `ctrl-D` and `ctrl-\` which should behave like in bash.

In interactive mode:

    - `ctrl-C` displays a new prompt on a new line.
    - `ctrl-D` exits the shell.
    - `ctrl-\` does nothing.

