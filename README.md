<h1 align="center">
	42Cursus minishell
</h1>

## 🗣️ About
42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

## 📋 Final grade : 125/125

`@root` directory

* [**📁 includes:**](includes/) contains the program's headers.
* [**📁 libft:**](libft/) contains the source code of the `libft` library, which is used in the program.
* [**📁 src:**](srcs/) contains the source code of the program.
* [**📄 Makefile**](Makefile) - contains instructions for compiling the program and testing it.

## 🚀 Installation

### Requirements

The program is written in C language for **Linux** distributions and thus needs the **`clang` compiler** and some standard **C libraries** including `readline.h` to run.

### Instructions

1. Clone this repository :
```
git clone https://github.com/Ry4nnnn/42_minishell.git
```

2. `cd` into the root directory :
```
cd 42_minishell
```

3. Compiling the Program :
```
Using ``make`` will create the ``minishell`` executable.
```

4. Simply execute the executable with :
```
./minishell
```

## 🛠️ Features

- Builtins: 
	- `cd` 
	- `pwd` 
	- `echo` with `-n` flag
	- `export`
	- `unset`
	- `env`
	- `exit`

- Redirections :
    - `<` Redirect input
    - `>` Redirect output
    -  `<<` Heredoc
    - `>>` Redirect output with append

- Signals:
	- `Ctrl-C`
	- `Ctrl-D`
	- `Ctrl-\`

Parser opens quotes `'` `"` like in bash and handles `\` even in `'` `"` different context.

Commands work with absolute and relative paths.

## Available options

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.

You can separate commands with ``;``, as well as use redirections ``>`` ``>>`` ``<`` and pipes ``|``.

Environment variables are handled, like ``$HOME``, including the return code ``$?``.

Finally, you can use ``Ctrl-C`` to interrupt and ``Ctrl-\`` to quit a program, as well as ``Ctrl-D`` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.

### Credit

This two-person project was done with [Ray](https://github.com/wangxuerui2003).

