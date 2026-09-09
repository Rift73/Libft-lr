*This project has been created as part of the 42 curriculum by aaminudd*

# Libft

## Description

Libft is a static C library that implements 43 functions in this subject. 
It provides ASCII classification and case conversion, byte copying and comparison, 
string searches and bounded copies, integer conversion, allocated string operations, 
file-descriptor output, and singly linked-list operations.

The public interface is declared in `libft.h`. Each `ft_*.c` file implements
one public function and the helpers are static. Memory functions use explicit byte
counts, while string functions use the terminating zero byte. Allocation
functions return owned storage on success and NULL on allocation failure.
`ft_split` returns an allocated pointer array containing allocated words and
a final NULL. List nodes store content pointers; deletion callbacks define
how that content is released. No global variables are used.

## Instructions

Run `make` to compile all mandatory functions into `libft.a` using
`cc -Wall -Wextra -Werror` and `ar`. There are no optional bonus files.

```sh
make
make clean
make fclean
make re
```

`clean` removes object files; `fclean` also removes the archive. `re` rebuilds
from scratch. An unchanged build does not recompile or relink.

To use the library, include `libft.h` in a C caller and link the archive:

```sh
cc -Wall -Wextra -Werror -I. caller.c libft.a -o caller
```

## Resources

- The supplied Libft version 19.3 subject defines the required interfaces.
- System manual pages: `man strlen`, `man memmove`, `man malloc`,
  and `man write`.
- [GNU C Library manual](https://sourceware.org/glibc/manual/)
- [GNU make manual](https://www.gnu.org/software/make/manual/)