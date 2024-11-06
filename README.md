<h1 align="center">MINISHELL</h1>

## Overview

The goal of this project is to create a simple shell and gain a deeper understanding of processes and file descriptors.

<br>

## Description

The shell should:
- Display a prompt while waiting for a new command.
- Maintain a functional command history.
- Locate and execute the correct executable (based on the PATH variable or by using relative or absolute paths).
- Avoid using more than one global variable to signal reception of an alert. \
Think about what this implies: this approach prevents your signal handler from accessing your main data structures.

> [!WARNING]
> This global variable may only provide the signal number received and cannot contain any other information or data. Therefore, it is forbidden to use "norm" type structures as global variables.

- Do not interpret unclosed quotes or special characters not specified in the prompt, such as `\` (backslash) or `;` (semicolon).
- Ensure that `'` prevents the shell from interpreting metacharacters in the quoted sequence.
- Ensure that `"` prevents the shell from interpreting metacharacters in the quoted sequence except for `$` (dollar sign).
- Implement redirections:
  - `<` should redirect input.
  - `>` should redirect output.
  - `<<`  should receive a delimiter, then read from the current input source until a line containing only the delimiter appears. However, it does not need to update the history.
- Implement pipes (`|` character). The output of each command in the pipeline should be connected via a pipe to the input of the next command.
- Handle environment variables (`$` followed by characters) that should expand to their values.
- Handle `$?`, which should expand to the exit status of the most recently executed command in the pipeline.
- Handle `ctrl-C`, `ctrl-D`, and `ctrl-\\`, to function as in Bash.
- When in interactive mode:
  - `ctrl-C` prints a new prompt on a new line.
  - `ctrl-D` terminates the shell.
  - `ctrl-\\` does nothing.
- Should implement the built-ins:
  - `echo` with the `-n` option.
  - `cd` only with a relative or absolute path.
  - `pwd` without options.
  - `export` without options.
  - `unset` without options.
  - `env` without options or arguments.
  - `exit` without options.

> [!TIP]
> You do not need to implement "forbidden" shell operators such as `&&` or `||`.

<br>

## Guidelines

|       Program name     |           minishell         |
|:-----------------------|:----------------------------|
|     Files to submit    |      Makefile, *.h, *.c     |
|         Makefile       | NAME, all, clean, flean, re |
|  Authorized functions  | readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history, printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, wait3, wait4, signal, sigaction, kill, exit, getcwd, chdir, stat, lstat, fstat, unlink, execve, dup, dup2, pipe, opendir, readdir, closedir, strerror, perror, isatty, ttyname, ttyslot, ioctl, getenv, tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs |
| Using libft is allowed |             Yes             |

> [!NOTE]
> The readline function may produce some leaks that you do not need to fix. This does not mean that your code — yes, the code you have written — can produce leaks.

<br>

## Compiling and Running

To compile the shell, simply run `make`. This will generate an executable called `minishell`.

To start the shell, use:

```
./minishell
```

Once inside `minishell`, you can execute commands just as you would in Bash.

<br>

## Authors
- [@gonzalonao](https://github.com/gonzalonao)
- [@AMarqs](https://github.com/AMarqs)
