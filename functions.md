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

-> If `clear_undo` is non-zero, the undo list asociated with the current line is cleared.

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
***A signal is a sort of notification message used in Unix/Posix OS. It is sent to a running program to notify it of some event and the system interrupts the process's normal execution to trigger a specific reaction (like terminating it).***

```
void  (*signal(int signum, void (*handler)(int)))(int);
```
-> Sets a function to handle a signal action.

-> `signum` is the signal number that you need to handle.

-> A lot of signal are predefined (like `SIGINT`(interupt signal), `SIGABRT`(abort signal)...)

-> `handler` is  pointer to a function that takes an integer as an argument and returns void. So when the process receives the specified signal this function is called. 

-> Special `handler` : `SIG_IGN` = the process ignores the signal - `SIG_DFL` = the process does default action for the signal.

-> ***returns*** the previous handler for the signal, if an error occured it returns `SIG_ERR`.

-> This function is not recommended.

-> Bon article qui explique les concepts : [ici](https://www.codequoi.com/envoyer-et-intercepter-un-signal-en-c/)

### sigaction
```
int  sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
-> Used to change the action of a process when it receives a ***specific signal***.

-> `signum` is the signal number we want to handle.

-> `act` is a pointer to the structure 'sigaction' which specifies the new action for the signal handler.

-> `oldact` is a pointer to the same stucture which will store the old action signal. If no need to save put it to `NULL`.

-> ***returns*** 0 if ok and -1 in case of error.

```
struct sigaction {
    void     (*sa_handler)(int); // pointer to signal handling function
    void     (*sa_sigaction)(int, siginfo_t *, void *);
    sigset_t   sa_mask; //is a set of signals to be blocked during execution
    int        sa_flags; // set of flags which modify the behavior
    void     (*sa_restorer)(void); // not used in the system...
};
```

example : 
```
void	sigint_handler(int signal);

void	set_signal_action(void) {
	struct sigaction action;
 	bzero(&action, sizeof(action));
 	action.sa_handler = &sigint_handler;
	sigction(SIGINT, &act, NULL);
 }
```
 

### sigemptyset
```
int	sigemptyset(sigset_t *set);
```
-> This function is used to initialize a signal set to be empty. It usually used with other signal handling function like `sigaction`.

-> `set` is a pointer to the stucture 'sigset_t' that we want to initialize to empty.

-> ***returns*** 0 if success and -1 if an error occured.

-> The actual structure `sigset_t` is not defined in the POSIX standard !! Shouldn't manipulate this struct...

### sigaddset
```
int	sigaddset(sigset_t *set, int signo);
```
-> This function adds the signal specified by `signo` to the signal set pointed to by `set`.

-> ***returns*** 0 if ok and -1 if error.

### kill
```
int	kill(pid_t pid, int sig);
```
-> `pid` is the the process ID to which the signal will be sent.

If the value is `> 0` the signal is sent with the process id.

Else if value is `0` the signal is sent to every process in the process group of the calling process.

Else if value is `-1` the signal is sent to every process for which the calling process has permission to send signals, except for process 1.

And if value is `< -1` the signal is sent to every process in the group.

-> `sig` is the signal number that we want tot send. If `sig` is 0, then no signal will be sent...

-> ***returns*** 0 if success but -1 if an error occured.

example : 
```
while (i < 3) {
	kill(pid[i], SIGKILL);
	i++;
}
```

### getcwd
```
char	*getcwd(char *buffer, size_t size);
```
-> This function is used to get the current working directory of the process.

-> `buffer` is pointer where the current working directory will be stored.

-> `size` is the size of the buffer.

-> ***returns*** a pointer to the buffer if the function succeded or `NULL` if not. Beware of the `size` we sent to `getcwd` because if the absolute pathname of the current working directory (including `NULL-terminator`) exceeds the `size` bytes we have an error. (should have an application to check for this error and allocate a larger buffer if necessary)

example :
```
char buf[1024];

if (getcwd(buf, sizeof(buf) != NULL) {
	printf("Current working directory : %s\n", buf);
}
```

### chdir
```
int	chdir(const char *path);
```
-> This function is used to change the current working directory of the process.

-> `path` is a string that specifies the path to the new working directory.

-> ***returns*** 0 if it's a success but -1 on error.

### stat
```
int	stat(const char *restrict path, struct stat *restrict buf);
```
-> This function is used to get the file status information.

-> `path` is a string that specifies the path to the file.

-> `buf` is a pointer to the structure `stat` where the file status information will be stored.

-> ***returns 0 if success else it's a -1.

```
struct stat {
	    dev_t     st_dev;     /* ID of device containing file */
	    ino_t     st_ino;     /* inode number */
	    mode_t    st_mode;    /* protection */
	    nlink_t   st_nlink;   /* number of hard links */
	    uid_t     st_uid;     /* user ID of owner */
	    gid_t     st_gid;     /* group ID of owner */
	    dev_t     st_rdev;    /* device ID (if special file) */
	    off_t     st_size;    /* total size, in bytes */
	    blksize_t st_blksize; /* blocksize for file system I/O */
	    blkcnt_t  st_blocks;  /* number of 512B blocks allocated */
	    time_t    st_atime;   /* time of last access */
	    time_t    st_mtime;   /* time of last modification */
	    time_t    st_ctime;   /* time of last status change */
}
```
### lstat
```
int	lstat(const char *restrict path, struct stat *restrict buf);
```
-> This function i similar to `stat`, but the named file is a symbolic link, `lstat` returns informations about the link itself and not the file it refers to.

-> `path` specifies the path to the file.

-> `buf` point to the struct `stat` whre info will be stored.

-> ***returns*** 0 if ok, -1 if not.

### fstat
```int	fstat(int fd, struct stat *buf);
```
-> This function is used to get file status information about an open file.

-> `fd` the file descriptor of the open file.

-> `buf` point to the sturcture `stat` and tores the inofrmation there.

-> ***returns*** 0 if ok, -1 if not.

### opendir
```
DIR *opendir(const char *name);
```
-> This function is used to open a directory flow corresponding to a given directory, so that the contents of the directory can be retrieved.

-> `name` is representing the path to the dir.

-> ***returns*** a pointer to a `DIR` structure representing the directory flow. But if an error occurs it returns NULL.

-> Do not forget to close the directory after using it.

### readdir
```
#include <dirent.h>
struct dirent	*readdir(DIR *dirp);
```
-> This function is used to read a directory entry from a directory flow. We can retreive the contents od the dir.

-> `dirp` points to a `DIR` structure representing the directory flow.

-> ***returns*** a pointer to structure `dirent` representing the next directory flow. And if no more entries to read or if an error occurs the function returns NULL.

example :
```
struct dirent  *entry;
DIR *dir = opendir("/path/to/directory");
// protection if NULL
while ((entry = readdir(dir)) != NULL)
	printf("%s\n", entry->d_name);
```
### closedir
```
#include <dirent.h>
int	closedir(DIR *dirp);
```
-> This function is used to close a directory flow that was previously opened by `opendir`. We must always close directories.

-> `dirp` points to structure `DIR` which representes the directory flow.

-> ***returns*** 0 if success and -1 if error.

### strerror
```
#include <string.h>
char	*strerror(int errnum);
```
-> This function returns a message error according to the error code.

-> `errnum` the error code.

-> ***returns*** a pointer to a string that describes the error code passed in argument.

### isatty
```
#include <unistd.h>
int	isatty(int fd);
```
-> This function is used to check if a file descriptor refers to a terminal. In case where the program is being run interactively / is being redirected to a file / is piped to another program etc, it is useful to know if a fd refers to a TTY.

-> `fd` is the file descriptor we want to check.

-> ***returns*** 1 if `fd` refers to a terminal and returns 0 if it doesn't. If error returns 0.

example :
```
if (isatty(STDOUT_FILENO))
	printf("STDOUT is a terminal\n");
```

### ttyname
```
#include <unistd.h>
char	*ttyname(int fd);
```
-> This function is used to get the name of the terminal associated with a given file descriptor.

-> `fd` is the file descriptor that we want to get the terminal name.

-> ***returns*** a pointer to a string containing the na,e of the terminal. And if `fd` is not associated with a terminal or if an error occured it returns NULL.


### ttyslot
```
#include <unistd.h>
int	ttyslot(void);
```
-> This function is used to get the index of the current process's controlling terminal in the system's list of terminal.

-> ***returns*** the index and if the process does't have a controlling terminal, or if any error occured it returns 0.

### ioctl
```
#include <sys/ioctl.h>
int	ioctl(int fd, unsigned long request, ...);
```
-> ioctl = means "input/output control".

-> This function is used to control subjacent devices from special files in the OS based on Unix. And this function can modify the device's behaviour, espacially to configure specific features that do not conform well to the UNIX I/O flow model. It is useful to communicate between devices like tty, network interfaces, USB etc.

-> `fd` is obtained from opening a device file.

-> `request` code is specific to the device driver and operation.

-> `...` is a pointer to variable arg, a memory used to transfer data between the program and the device driver.

-> This function can beused for a lot of task = configuring a terminal / handling USB devices .... Every evices can have their own requests defined in header.

-> ***returns*** 0 on success and -1 on error.

example :
```
int fd = open("/dev/mydevice", O_RDWR);
//protection file

int result = ioctl(fd, MYDEVICE_IOCTL_COMMAND, NULL);
if (result == -1)
{
	perror("ioctl errror");
	close(fd);
	return 1;
}
printf("the ioctl command was successful\n");
(...)
```
### getenv
```
char	*getenv(const char *name);
```
-> `getenv` = "get environment". So this function is used to retreive the value of an environment variable from the process's environment.

-> `name` of the environment variable we want to retreive.

-> ***returns*** a pointer to a string which is the value of the environment variable. If anything is found it returns a NULL pointer.

### tcsetattr
```
#include <termios.h>
int	tcsetattr(int fd, int optional_actions, const struct termioss *termios_p);
```
-> This function is used to change the parameters of terminal device.

-> `fd` of the terminal (usually STDIN_FILENO).

-> `optional_actions` specifies the changes that shoult take effect. It can be one of = 

- `TCSANOW` = changes occur immediately.
- `TCSADRAIN` = changes occur after all output written to `fd` has been transmitted.
- `TCSAFLUSH` = changes occur after all output written to `fd` has been transmitted AND all input that has been received but not read will be discarded before the change.

-> `termios_p` is pointer to the structure `termios` that contains the new terminal parameters.

-> ***returns*** 0 on success and -1 on error.

example :
```
#define STDIN_FILENO 0

main() {
struct termios original;
struct termios noecho;
// execute code before changes
tcgetattr(STDIN_FILENO, &original); // obtain current terminal configuration
noecho = origal; // duplicate current config
noecho.c_flag &= ~ECHO; // turn off the ECHO flag
tcsetattr(STDIN_FILENO, TCSANOW, &noecho); // set terminal to the modified config
//apply code with the changes
tcseattr(STDIN_FILENO, &original); // restore original config
```

```
struct termios {
    tcflag_t c_iflag;  /* input modes */
    tcflag_t c_oflag;  /* output modes */
    tcflag_t c_cflag;  /* control modes */
    tcflag_t c_lflag;  /* local modes */
    cc_t c_cc[NCCS];   /* control characters */
};
```
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
