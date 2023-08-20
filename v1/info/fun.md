# FUNÇÕES PERMITIDAS

## Resumo

These are all functions that are used to interact with the operating system and manage system resources in various ways:

- `readline`: Read a line from the standard input. It also has history capabilities.

- `rl_clear_history`: Clear the history of previous lines read by readline.

- `rl_on_new_line`, `rl_replace_line`, `rl_redisplay`: Functions to manipulate the line currently being entered in readline.

- `add_history`: Add a line to the readline history.

- `printf`: Output formatted data.

- `malloc`, `free`: Allocate and deallocate dynamic memory.

- `write`: Write to a file descriptor.

- `access`: Check user's permissions for a file.

- `open`, `read`, `close`: Open, read from, and close a file.

- `fork`: Create a new process.

- `wait`, `waitpid`, `wait3`, `wait4`: Wait for a process to change state.

- `signal`, `sigaction`, `sigemptyset`, `sigaddset`, `kill`: Functions to work with signal handling.

- `exit`: Cause normal process termination.

- `getcwd`, `chdir`: Get and change the current working directory.

- `stat`, `lstat`, `fstat`: Get file status.

- `unlink`: Remove a file.

- `execve`: Execute a program.

- `dup`, `dup2`: Duplicate a file descriptor.

- `pipe`: Create pipe.

- `opendir`, `readdir`, `closedir`: Open, read from, and close a directory.

- `strerror`, `perror`: Return a string describing error number.

- `isatty`, `ttyname`, `ttyslot`: Test whether a file descriptor refers to a terminal, return name of a terminal, return a terminal slot number.

- `ioctl`: Control device.

- `getenv`: Get an environment variable.

- `tcsetattr`, `tcgetattr`: Get and set terminal attributes.

- `tgetent`, `tgetflag`, `tgetnum`, `tgetstr`, `tgoto`, `tputs`: Functions to work with the Termcap library.
