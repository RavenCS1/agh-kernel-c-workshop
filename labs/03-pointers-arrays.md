# Practice tasks — pointers, arrays, strings

> **Compilation:** `gcc -Wall -Wextra -Wpedantic -std=c2x -o prog prog.c`
> **Memory check:** `valgrind --leak-check=full ./prog`

## Extended practice tasks

### 2D array operations

**Constraints:** no global variables; all printing happens only in `main`.

1. Given two arrays of real numbers with 3-element rows:
   ```
   A_1: 1.3, 3.4, 1.1, 26.3, 34.4, 12.3, 8.1
   A_2: 11.3, 23.4, 10.1, -2.3, -4.4, 2.3, 0.1, 13.1, 6.1, 14.4
   ```
   Write a `sumuj` function that sums the elements of a 2D array whose rows have three elements. For each array:
   - print the whole array with a single call to the printing procedure (without the `&` operator),
   - print the rows one by one (without `&`),
   - print the number of rows (computed with `sizeof`) and the sum of the elements.

2. Allocate a dynamic array `table` of integers whose size is given by the user. Fill it with random values in the range `<-5, 5>`. Copy the even elements into a dynamic array `arg_p` and the odd ones into `arg_n` (zero counts as even).

   **`arg_p` and `arg_n` must grow as elements are added, while `table` must shrink.**
   ```
   table -> -3, 0, 4, 3, -1, 1, 2
   arg_p -> 2, 4, 0
   arg_n -> 1, -1, 3, -3
   table -> (empty)
   ```

3. Create a 2D integer array `TAB` with dimensions `N` (rows) and `M` (columns) fixed with `#define`. Fill it with random values in `<-5, 5>`.

   - Using the provided `find_min_ind` (returns the index of the minimum in a 1D range), write a `tab_min` function that takes a 2D array with rows of length `M` and returns a dynamically allocated array of the indices of the minimum value in each row.

     ```c
     int find_min_ind(int* T_F, int* T_L) {
         int min = 0;
         for (int i = 1; i < T_L - T_F; i++)
             if (T_F[min] > T_F[i]) min = i;
         return min;
     }
     ```

   - In `main`, call `tab_min` for `TAB`. Using the array of row-minimum indices, find the minimum value in the whole array and print its row number, column number, and value. A solution that avoids an extra array is preferred.

   - Write a `row_number` function that returns a **pointer to a variable** holding the number of the row containing the minimum element of a 2D array with rows of length `M`. It must use `find_min_ind`. Test it: print the row number, then print the elements of that row with the printing procedure (without `&`). Keep the number of variables to a minimum.

### Array and pointer-array swapping

1. Given a `swap` procedure that swaps `n_bytes` of memory:
   ```c
   void swap(void* a, void* b, size_t n_bytes) {
       char* p_a = a;
       char* p_b = b;
       for (size_t i = 0; i < n_bytes; i++) {
           char temp = *p_a;
           *p_a = *p_b;
           *p_b = temp;
           p_a++;
           p_b++;
       }
   }
   ```
   - Write a `swap_tab` procedure that swaps the contents of two arrays `A` and `B` of the same length `n`, using `swap`.
   - Write a `swap_rows` procedure that swaps row `x` with row `y` in a 2D array, using `swap_tab`.

   Test, printing the arrays before and after the swap:
   ```
   tab_1  = 4×5, rows filled with 1,2,3,4   → swap rows 1 and 2 with rows 3 and 4 in a single swap_rows call
   tab_22 = 5×2, rows filled with 1,2,3,4,5 → swap row 1 with row 2 using swap_tab
   ```

2. Write a procedure that sorts the rows of a 2D array of any dimensions in ascending order by their row sum (simple selection sort; compute the sum with a `suma` function). Use `swap_rows`. Test on:
   ```
   tab_A = 4×6, rows: {1,-4,1,2,11}, {12,2,2}, {72,2,-32,2}
   tab_B = 5×3, rows: {1,-24,1}, {9,32,2}, {5,64,1}, {3,32,1}, {1,-1,2}
   ```

3. A program using arrays of pointers — **apart from declarations and initialisation, do not use the identifiers `TAB_1` and `TAB_2`**; refer to them only through the pointers `WSK` and `WSK_1`.

   - Define a `double` array `TAB_2` (7 elements) and an array `TAB_1` of pointers to `double` (7 elements), where `TAB_1[i]` points to `TAB_2[i]`. Set `WSK = WSK_1 = TAB_1`. Through `WSK`, print the values of `TAB_2` (with the printing procedure) and the addresses stored in `TAB_1`.

   - Using the provided `find_min_wsk` (returns a pointer to the minimum in a `double` array), write a `find_min_wsk_wsk` function whose argument is an array of pointers; it returns a pointer to the **element of the pointer array** that points to the minimum value in the target array. Print the address and the value of the minimum.

     ```c
     double* find_min_wsk(double* T_F, double* T_L) {
         double* min = T_F++;
         while (T_F < T_L) {
             if (*min > *T_F) min = T_F;
             T_F++;
         }
         return min;
     }
     ```

   - Perform a cyclic shift of the elements of `TAB_2` upwards, **using the pointers in `TAB_1`**. Print both arrays.

   - Write a `swap_p` function that swaps the contents of two pointer-to-`double` variables. Use it to **reverse** the contents of `TAB_1` (so the pointers now point from the end). Print `TAB_2` twice: once through the `TAB_1` identifier and once with the printing procedure through `WSK` — the two results will differ, because `TAB_1` now reads through the rearranged pointers.
