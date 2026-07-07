# Laboratory tasks — pointers, arrays, dynamic memory

> **Compilation:** `gcc -Wall -Wextra -Wpedantic -std=c2x -o prog prog.c`
> **Memory check:** `valgrind --leak-check=full ./prog`
>
> **General requirements:**
> - compiles with no warnings,
> - no memory leaks,
> - **no pointer casts** (explicit or implicit),
> - **no `&` operator** (unless a task explicitly allows it),
> - no global variables,
> - all printing happens **only** in `main`.

## Provided helper — `swap_all`

Available in every task that requires swapping. Call it directly:

```c
void swap_all(void* a, void* b, size_t size) {
    char* pa = a;
    char* pb = b;
    for (size_t i = 0; i < size; i++) {
        char temp = *pa;
        *pa = *pb;
        *pb = temp;
        pa++;
        pb++;
    }
}
```

---
---

## Array and matrix tasks

### Swapping arrays and rows

**(a)** Write a procedure `swap_tab` that swaps the contents of two arrays `A` and `B` of the same length `n`, using `swap_all`.

**(b)** Write a procedure `swap_rows` that swaps row `x` with row `y` in a 2D array `TAB`, using `swap_all`. The row size must be derived from the `TAB` identifier itself (do not hard-code it).

Test on the arrays below, printing each one before and after the swap:
```
tab_1  = 4×5, rows filled with 1,2,3,4      → swap row 1 with row 3
tab_22 = 5×2, rows filled with 1,2,3,4,5    → swap row 1 with row 2
```

### Array with an arbitrary index range

Write an allocation function that dynamically allocates a 1D array of `double` whose **valid indices are the closed range `[i_min, i_max]`**. For example, after allocating with `i_min = -5`, `i_max = 2`, the array may be used from index `-5` to index `2`. The function checks that the range is valid and that allocation succeeded (otherwise it returns a null pointer).

Write a matching free function that safely releases such an array: no dangling pointers, and it must not attempt to free an empty (null) pointer.

**Program:**
- Create an array with indices `-2..4`, all elements set to `8.8`.
- Print the whole array (for each element: its index, value, and address).
- Fill the array with random values **except** the first and last element (which keep `8.8`).
- Print the whole array again the same way.
- Free the memory, then attempt to free it **again** — the program must not crash.

### Merging sorted arrays

Write a function whose arguments are two **ascending-sorted** integer arrays. It creates and returns a new array that is their union: values that appear in either input, with duplicates removed, sorted ascending.

**Constraint:** the new array must **grow** as elements are added. Do **not** allocate an array of size equal to the sum of the two lengths and only then sort and remove duplicates — exploit the fact that both inputs are already sorted.

In `main`, print the example inputs and the resulting array.
```
arg_1 = {10, 12, 12, 15, 15, 16, 16, 18, 19}
arg_2 = {10, 11, 11, 12, 14, 15, 16, 16, 18, 18, 18, 19, 19, 20, 20}
→ 10, 11, 12, 14, 15, 16, 18, 19, 20
```

---
---

## String tasks

### Joining strings

Write a function `join` that takes an array of strings and its length and concatenates the **non-repeating** elements into a single string, using functions from `<string.h>`.

In `main`: first print all command-line arguments (or a message if there are none); at the end print the result of calling `join` on the array of arguments.
```
./prog Ala ma psa a Ola ma kota i Psa
arguments: Ala / ma / psa / a / Ola / ma / kota / i / Psa
result:    AlamapsaaOlakotaiPsa
```

### snake_case and camelCase

**(1)** Write a function that dynamically allocates and returns a single string built by joining all command-line arguments with an underscore (the `snake_case` naming convention). You must use `strlen` and `strncpy` (do not copy characters by hand).
```
./prog raz dwa trzy 4.0  →  raz_dwa_trzy_4.0
```

**(2)** Convert the resulting string (as a new string) to the `camelCase` convention. Use `strtok`, `strncpy`, and `strncat` (plus `strlen` and `toupper`).
```
./prog ala ma 3 koty i psa
snake_case: ala_ma_3_koty_i_psa
camelCase:  alaMa3KotyIPsa
```
All printing happens in `main`. With no arguments, print a suitable message.

### Pascal's triangle

Write a function that returns an array holding the `n`-th row of Pascal's triangle. Work on a 1D array and use `realloc`.
```
n = 1 → 1
n = 3 → 1 2 1
n = 6 → 1 5 10 10 5 1
```

---
---

## Practice tasks — easy

### L1
Write a function that dynamically allocates an array and fills it with consecutive integers from `a` to `b` inclusive (assume `a <= b`), returning a pointer to it (or a null pointer on failure). In `main`, call it for `3..9`, print, and free.

### L2
Write a function that returns the number of occurrences of a character `c` in a string `s`. Use **pointer arithmetic only** (no `[]`). Test with `s = "abracadabra"`, `c = 'a'`.

### L3
Write a function that dynamically allocates and returns a copy of a string (a hand-written equivalent of `strdup`), using `strlen` and `strcpy`; return a null pointer on failure. In `main`, duplicate `"Hello, world!"`, print, and free.

### L4
Write a function that fills a whole square `n × n` array with a given value, and a second function that prints such an array row by row. Test on a `4 × 4` array.

---

## Practice tasks — medium

### S1
Write a function that uses `realloc` to grow an array by one element, append a given value at the end, update the stored length, and return the new pointer (or a null pointer if `realloc` fails — in which case the original array must remain intact). In `main`, start from an empty array and append `10, 20, 30, 40, 50`, printing after each step.

### S2
Write a function that dynamically allocates and returns a new string that is the concatenation of two given strings, using `strlen`, `strcpy`, and `strcat`; return a null pointer on failure. Test with `("foo", "bar")` and `("", "test")`.

---

## Practice tasks — hard

### T2
Write a function that dynamically allocates a `rows × cols` matrix as an array of row pointers (each row a separately allocated array). On failure, any partially allocated memory must be freed before returning a null pointer. Write a matching free function. In `main`, allocate a `4 × 5` matrix, fill it so that element `(i, j)` equals `i * cols + j`, print it, and free it.

### T3
Write a procedure that sorts the rows of an `n × m` array in ascending order by their row sum (simple selection sort, swapping rows with `swap_all`). In `main`, test on:
```
{{3,3,3}, {1,1,1}, {4,4,4}, {2,2,2}}
```
Print the array before and after sorting.
