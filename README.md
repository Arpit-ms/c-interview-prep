# C Interview Prep

C fundamentals for embedded and firmware interviews. Pointers, strings, memory,
bit manipulation. Everything in C - no C++, no Python.

## libc/

Hand-written implementations of standard library primitives, with a
self-checking test harness. Written without reference, then compared against
glibc.

    gcc -Wall -Wextra -o mystring mystring.c && ./mystring

| Function | Point of interest |
|----------|-------------------|
| my_strlen   | size_t return, no terminator counted |
| my_strcpy   | returns original dst for chaining |
| my_strncpy  | pads with NUL; does NOT terminate if src >= n |
| my_memcpy   | void *, byte-wise, undefined on overlap |
| my_memmove  | overlap-safe; copies backward when dst > src |

## leetcode/

Solutions in C, chosen for firmware relevance - array traversal, pointer
arithmetic, in-place algorithms, bit manipulation. Not tree/graph/DP.
