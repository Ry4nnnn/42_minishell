<h1 align="center">
	42Cursus minishell
</h1>

## 🗣️ About
42_minishell, This project is about creating a simple shell terminal. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

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

### To install Readline library latest version

Click here to download: [readline-8.1](https://ftp.gnu.org/gnu/readline/readline-8.1.tar.gz)

Then run this : `./configure --prefix=$(pwd) && make && make install`

## 🛠️ Features

- Builtins: `cd` , `pwd` , `echo`, `export`, `unset`, `env`, `exit`

- Redirections: `<`, `>`, `<<`, `>>`

- Piping: `|`

- Signals:
	`Ctrl-C` - interrupts the program
	`Ctrl-D` - quits the program
	`Ctrl-\` - does nothing

- Working history supported.

- `'`, `"` quotes supported.

- `&&`, `||` operator supported.

- Wildcards `*` are supported.

- Exit status `$?` supported.

- Environment variables are handled, like `$HOME`

- Commands work with absolute and relative paths.

- Error Messages

## Credits

This two-person project was done with [Xue Rui](https://github.com/wangxuerui2003).

Thanks to [Xue Rui](https://github.com/wangxuerui2003)
