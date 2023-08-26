# PROGRAM PROGRESS

## Mandatory

- [ ] Your shell must implement the following builtins:
	- [ ] `echo` with option `-n`
	- [ ] `cd` with only a relative or absolute path
	- [ ] `pwd` with no options
	- [ ] `export` with no options
	- [ ] `unset` with no options
	- [ ] `env` with no options or arguments
	- [ ] `exit` with no options
- [ ] Display a **prompt** when waiting for a new command.
- [ ] Have a working **history**.
- [ ] Search and launch the right executable (based on the **PATH** variable or using a relative or an absolute path).
- [ ] Not interpret unclosed quotes or special characters which are not required by the subject such as `\` (backslash) or `;` (semicolon).
- [ ] Handle `'` (single quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence.
- [ ] Handle `"` (double quote) which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$` (dollar sign)
- [ ] Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
- [ ] In interactive mode:
	- [ ] <kbd>Ctrl</kbd>+<kbd>C</kbd> displays a new prompt on a new line.
	- [ ] <kbd>Ctrl</kbd>+<kbd>D</kbd> exits the shell.
	- [ ] <kbd>Ctrl</kbd>+<kbd>\\</kbd> does nothing.
- [ ] Handle <kbd>Ctrl</kbd>+<kbd>C</kbd>, <kbd>Ctrl</kbd>+<kbd>D</kbd> and <kbd>Ctrl</kbd>+<kbd>\\</kbd> which should behave like in bash.
- [ ] Implement redirections:
	- [ ] `>` should redirect output.
	- [ ] `<` should redirect input.
	- [ ] `>>` should redirect output in append mode.
	- [ ] `<<` should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history!
- [ ] Implement pipes (`|` character). The output of each command in the pipeline is connected to the input of the next command via a pipe.
- [ ] Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.
	- [ ] Exit/Error status management.

## Bonus

- [ ] `&&` and `||` with parenthesis for priorities.
- [ ] Wildcards `*` should work for the current working directory.
