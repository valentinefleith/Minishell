# Functions

### `readline` 
`char  *readline(char *prompt);`

`readline` will read a line from the terminal and return it, using `prompt` as a prompt.
If `prompt` is `NULL` or empty string, no prompt is issued. The line is allocated with `malloc`. 
The line returned has the final newline removed, so only the text of the line remains.

`returns` the text of the line read. A blank line returns the empty string. If the `EOF` is encountered while reading a line,
and the line is empty, `NULL` is returned. If an EOF is read with a non-empty line, it is treated as a newline.
-> This is the basic manual for bsic use, must read "The GNU Readline Library" for more informations...

example: `char  *line = readline("Enter a line: ");`
[see how to program with readline] :(https://web.mit.edu/gnu/doc/html/rlman_2.html)

### rl_clear_history

### rl_on_new_line

### rl_replace_line

### rl_redisplay

### add_history

### printf - malloc - write - access - open - read - close - fork - wait - waitpid - wait3 - wait4 - exit
### unlink - execve - dup - dup2 - pipe - perror

### signal

### sigaction

### sigemptyset
### sigaddset
### kill
### getcwd
### chdir
### stat
### lstat
### fstat
### opendir
### readdir 
### closedir
### strerror
### isatty
### ttyname
### ttyslot
### ioctl
### getenv
### tcsetattr
### tcgetattr
### tgetent
### tgetflag
### tgetnum
### tgetstr
### tgoto
### tputs
