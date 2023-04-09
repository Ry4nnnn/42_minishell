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

- Builtins: `cd` , `pwd` , `echo`, `export`, `unset`, `env`, `exit`

- Redirections: `<`, `>`, `<<`, `>>`

- Piping: `|`

- Signals:
	- `Ctrl-C` - to interrupt the program and 
	- `Ctrl-D` - to quit the program
	- `Ctrl-\` - should do nothing

- Working history supported.

- `'`, `"` quotes supported.

- `&&`, `||` operator supported.

- Exit status supported `$?`.

- Environment variables are handled, like `$HOME`

- Commands work with absolute and relative paths.

## Available options

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. ``'`` and ``"`` work the same as bash, except for multiline commands.


This two-person project was done with [Ray](https://github.com/wangxuerui2003).

