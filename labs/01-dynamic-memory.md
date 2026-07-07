# Practice tasks — dynamic memory and arrays

> **Compilation:** `gcc -Wall -Wextra -Wpedantic -std=c2x -o prog prog.c`
> **Memory check:** `valgrind --leak-check=full ./prog`
>
> **General requirements (as in the lab):**
> - compiles with no warnings,
> - no memory leaks,
> - `int main(void)` and `return EXIT_SUCCESS`,
> - **do not use `NULL`** — use `0`,
> - no global variables; all printing happens **only** in `main`.

---

## Task 1 — Dynamic array of integers

Write three functions that manage a dynamic array of `int`:

- a **create** function that takes a length `n`, allocates that many **zero-initialised** elements, and returns a pointer to the array (or a null pointer on allocation failure);
- a **resize** function that changes the array's length to `n` elements and returns the (possibly relocated) pointer, or a null pointer on failure — **on failure the original array must remain valid**;
- a **destroy** function that frees the array.

**Test sequence in `main`:**
1. Create 5 elements, fill them with `1..5`, print.
2. Resize to 8 elements — the three new elements must be `0` — print.
3. Resize to 3 elements, print.
4. Destroy.

---

## Task 2 — 2D matrix of `double`

Write two functions:

- an **allocation** function taking a number of rows and columns. It allocates an array of row pointers, and for each row a **zero-initialised** row of `cols` doubles. If any allocation fails it must free everything already allocated and return a null pointer.
- a **free** function that releases every row and then the array of row pointers. **Order matters:** rows first, then the pointer array.

**In `main`:**
1. Allocate a `3×4` matrix.
2. Fill it so that element `(i, j)` equals `i * 4 + j` (values `0..11`).
3. Print it row by row.
4. Free it.

---

## Task 3 — Filtering an array

Write a **filter** function taking a source array, its length `n`, a threshold, and a pointer through which it reports the output length. It returns a newly allocated array holding only the elements **strictly greater** than the threshold, and returns a null pointer on allocation failure. The caller is responsible for freeing the result.

**Requirements:**
- The result must be exactly the right size (no unused trailing capacity).
- Handle the empty result in a well-defined way (reallocating to length `0` is implementation-defined in C23).

**Tests:**
- Input `{3, 1, 4, 1, 5, 9, 2, 6}`, threshold `3` → `{4, 5, 9, 6}` (length `4`).
- Threshold `10` (no element matches) — the reported length is `0`.

---

## Task 4 — Merging two sorted arrays (no duplicates)

Write a function that merges two **ascending-sorted** arrays into a single ascending-sorted array **without duplicates**. It takes both arrays with their lengths and a pointer through which it reports the output length; it returns the new array (the caller frees it) or a null pointer on allocation failure.

**Constraint:** the result array must **grow as elements are added**. Do **not** allocate an array of size `na + nb` and then sort and remove duplicates — exploit the fact that both inputs are already sorted.

**Test data:**
```
a = {10, 12, 12, 15, 15, 16, 16, 18, 19}
b = {10, 11, 11, 12, 14, 15, 16, 16, 18, 18, 18, 19, 19, 20, 20}
→ 10 11 12 14 15 16 18 19 20   (length 9)
```

---

## Task 5 — Row averages of a 2D array

Write a function that computes the average of each row of a 2D array whose number of columns `M` is fixed (e.g. `5`). It takes the number of rows and the 2D array, allocates and returns an array of that many `double` values (the caller frees it), or a null pointer on allocation failure.

**In `main`:**
1. Use a static array `data[4][M]`.
2. Fill it so that element `(i, j)` equals `i * M + j + 1` (values `1..20`).
3. Call the function.
4. Print the four averages — expected `3.0, 8.0, 13.0, 18.0`.
5. Free the result.
