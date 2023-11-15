# simple_Shell Project

## Description

This project is a custom shell implementation, inspired by the Unix shell, that allows users to interact with an operating system through a command-line interface. The shell supports various features, including built-in commands, piping, multiple commands on a single line, and special operators like `&&`, `||`, `$`, `?`, and `#`. It is designed to work in both interactive and non-interactive modes.

## Features

- Custom command-line shell.
- Built-in commands like `cd`, `alias`, and more.
- Pipe (`|`) support for connecting commands.
- Ability to run multiple commands on a single line using `;`.
- Special operators for conditional execution (`&&` and `||`), variable substitution (`$`), command substitution (`#`), and error checking (`?`).
- Interactive and non-interactive modes.

## Flowchart

To get a visual representation of how the shell operates, you can refer to the flowchart [here](link-to-your-flowchart-image).

## Getting Started

To get started with the project, follow these steps:

1. Clone the repository: `git clone https://github.com/AbuArwa001/simple_Shell.git`
2. Build the shell: `make` (if applicable)
3. Run the shell: `./custom-shell`

## Usage

You can use the custom shell to interact with your system. Here are some examples of how to use the shell:

```sh
$ ls -l | grep my_file
$ echo "Hello, World!"
$ cd /path/to/directory
$ command1; command2
$ command1 && command2
$ command1 || command2
$ echo $VAR_NAME
$ echo #command
$ command1 || echo $?  # Check the exit status of command1
