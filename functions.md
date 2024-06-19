# Functions

### [READLINE BIBLE](https://tiswww.case.edu/php/chet/readline/rltop.html)

`#include <stdio.h>`
`#include <readline/readline.h>`
`#include <readine/history.h>`

### `char  *readline(char *prompt);`
***readline*** will read a line from the terminal and return it, used in command line interfaces.

If `prompt` is `NULL` or empty string, no prompt is issued. The line is allocated with `malloc`. 
The line returned has the final newline removed, so only the text of the line remains.

***readline returns*** the text of the line read. A blank line returns the empty string. If the `EOF` is encountered while reading a line, and the line is empty, `NULL` is returned. If an EOF is read with a non-empty line, it is treated as a newline.

example: `char  *line = readline("Enter a line: ");`

see how to program with readline : [ici](https://web.mit.edu/gnu/doc/html/rlman_2.html)

***readline variables***
These variables are available to function writers.
`char  *rl_line_buffer` This is the line gathered so far. It is possible to modify the contents of the line.

#### `void  rl_clear_history(void);`
->Clears the history list by deleting all of the entries of readline.

#### `int   rl_on_new_line(void);`
-> Tells to readline that the cursors is on a new line. 

#### `void rl_replace_line(const char *text, int clear_undo);`
-> Replaces the current line of readline with an other given text.

#### `void  rl_redisplay(void);`
-> Change what's displayed on the screen to reflect the current contents of `rl_line_buffer`

#### add_history
-> Adds a line to the readline history.

#### Allowed functions but already known.
printf - malloc - write - access - open - read - close - fork - wait - waitpid - wait3 - wait4 - exit
unlink - execve - dup - dup2 - pipe - perror

#### signal
-> Bon article qui explique les concepts : [ici](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)

`#include <signal.h>`

-> Sets a function to handle a signal action.

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
