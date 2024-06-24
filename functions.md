# Overview of how functions (allowed) work

### Bible of readline's library : [GNU Readline library](https://tiswww.case.edu/php/chet/readline/rltop.html)

### Includes
```
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
```
### Makefile
```-lreadline``` flag to link the library.

### Readline
```
char  *readline(char *prompt);
```
-> ***readline*** will read a line from the terminal and return it (used in command line interfaces).

-> If `prompt` is `NULL` or empty string, no prompt is issued. 

-> The line is allocated with `malloc`. 

-> The line returned has the final newline removed, so only the text of the line remains.

-> ***returns*** the text of the line read. A blank line returns the empty string. If the `EOF` is encountered while reading a line, and the line is empty, `NULL` is returned. If an EOF is read with a non-empty line, it is treated as a newline.

example: ```char  *line = readline("Enter a line: ");```

-> When called ***readline*** displays a prompt (if given) and waits for the user to give an input (line of text) in return.
While waiting for input ***readline*** provides some possibilities like : moving the cursos left and right on the line, deleting characters, cutting/pasting text, using history commands and recall previously entered lines.
Once the user presses the 'Enter key', it returns the text and if it is not empty added to history list.

-> If the user signals an EOF (like Ctrl-D) it returns a `NULL` pointer.

-> see how to program with readline/ some tips : [ici](https://web.mit.edu/gnu/doc/html/rlman_2.html)

-> Can cause leaks, no need to worry about it, it's a known issue.

#### Other readline functions

### rl_clear_history()
```
void  rl_clear_history(void);
```
-> Clears the history list by deleting all of the entries of readline.

-> After the call, the history list is empty because this function frees the memory.

example : 
```
if (strcmp(input, "clear_history") == 0) {
            rl_clear_history();
            printf("History cleared.\n");
```
### rl_new_line()
```
int   rl_on_new_line(void);
```
-> Tells to readline that the cursors is on a new line. Doesn't affect the input or the history list.

### rl_replace_line("text", 0)
```
void  rl_replace_line(const char *text, int clear_undo);
```
-> Replaces the current line that readline is working with with an other given text. Doesn't affect the history list, but the replaced line will be added to the history.

example : 
```
if (strcmp(input, "replace_line") == 0) {
      rl_replace_line("This line has been replaced.", 0);
      printf("The readline \"%s\" -> was replace with: \"%s\"\n", input, rl_copy_text(0, rl_end));
}
else {
      add_history(input);
      printf("You entered: %s\n", input);
}
```

### rl_redisplay()
```
void  rl_redisplay(void);
```
-> Change what's displayed on the screen to reflect the current state of the readline's buffer.

### add_history("text")
```
void  add_history(const char *string);
```
-> Adds a line to the readline history list. So it is available for later recall.

### signal
```#include <signal.h>```
```
void  (*signal(int signum, void (*handler)(int)))(int);
```
-> Sets a function to handle a signal action.

-> `signum` is the signal number that you need to handle.

-> A lot of signal are predefined (like `SIGINT`(interupt signal), `SIGABRT`(abort signal)...)

-> `handler` is  pointer to a function that takes an integer as an argument and returns void. So when the process receives the specified signal this function is called. 

-> Special `handler` : `SIG_IGN` = the process ignores the signal - `SIG_DFL` = the process does default action for the signal.

-> ***returns*** the previous handler for the signal, if an error occured it returns `SIG_ERR`.

-> Bon article qui explique les concepts : [ici](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)

### sigaction
```
int  sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
-> Used to change the action of a process when it receives a ***specific signal***.

-> `signum` is the signal number we want to handle.

-> `act` is a pointer to the structure 'sigaction' which specifies the new action for the signal.

-> `oldact` is a pointer to the same stucture which will store the old action signal. If no need to save it write `NULL`.

```
struct sigaction {
    void     (*sa_handler)(int); // pointer to signal handling function
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask; //is a set of signals to be blocked during execution
    int        sa_flags; // set of flags which modify the behavior
    void     (*sa_restorer)(void); // not used in the system...
};
```

### sigemptyset
```
int  sigemptyset(sigset_t *set);
```
-> This function is used to initialize a signal set to be empty. It usually used with other signal handling function like `sigaction`.

-> `set` is a pointer to the stucture 'sigset_t' that we want to initialize to empty.

-> ***returns*** 0 if success and -1 if an error occured.

-> The actual structure `sigset_t` is not defined in the POSIX standard !! Shouldn't manipulate this struct...

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


#### Allowed functions but already known.
`printf` - `malloc` - `write` - `access` - `open` - `read` - `close` - `fork` - `wait` - `waitpid` - `wait3` - `wait4` - `exit`
`unlink` - `execve` - `dup` - `dup2` - `pipe` - `perror`
