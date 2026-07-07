/*
 * gdb_demo.c
 * ----------
 * A program designed to demonstrate various GDB debugging features:
 * breakpoints, watchpoints, stepping, inspecting variables,
 * modifying values at runtime, and argc/argv handling.
 *
 * Compile with:
 *   gcc -std=c2x -g -Wall -Wextra gdb_demo.c -o gdb_demo
 *
 * Run with arguments:
 *   ./gdb_demo hello 42
 *
 * Start GDB session:
 *   gdb ./gdb_demo
 *   (gdb) set args hello 42       <- set argc/argv before running
 *   (gdb) break main              <- breakpoint at main
 *   (gdb) break gdb_demo.c:65     <- breakpoint at line 65
 *   (gdb) watch result            <- watchpoint on variable
 *   (gdb) run
 *   (gdb) next                    <- step over
 *   (gdb) step                    <- step into
 *   (gdb) print sum               <- inspect variable
 *   (gdb) print arr[2]            <- inspect array element
 *   (gdb) set var sum = 999       <- modify variable at runtime
 *   (gdb) backtrace               <- print call stack
 *   (gdb) info locals             <- print all local variables
 *   (gdb) info args               <- print function arguments
 *   (gdb) display i               <- auto-display variable each step
 *   (gdb) continue                <- continue execution
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 10

/* Compute sum of an integer array */
int array_sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];   /* set a breakpoint here to watch sum grow */
    }
    return sum;
}

/* Compute factorial recursively - good for demonstrating backtrace */
int factorial(int n) {
    if (n <= 1)
        return 1;
    return n * factorial(n - 1);
}

/* Demonstrate pointer arithmetic */
void pointer_demo(int *arr, int n) {
    printf("Pointer walk:\n");
    for (int *p = arr; p < arr + n; p++) {
        printf("  addr: %p  value: %d\n", (void *)p, *p);
    }
}

/* Demonstrate string handling */
void string_demo(const char *input) {
    size_t len = strlen(input);
    printf("Input string : \"%s\"\n", input);
    printf("Length       : %zu\n", len);

    char *copy = malloc(len + 1);
    if (!copy) {
        fprintf(stderr, "malloc failed\n");
        return;
    }
    strcpy(copy, input);
    printf("Copy         : \"%s\"\n", copy);
    free(copy);
}

int main(int argc, char *argv[argc+1]) {
    printf("=== GDB Demo ===\n\n");

    /* Demonstrate argc/argv inspection */
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = \"%s\"\n", i, argv[i]);
    }
    printf("\n");

    /* Array demo */
    int arr[ARRAY_SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int result = array_sum(arr, ARRAY_SIZE);
    printf("Array sum: %d\n", result);   /* try: set var result = 0 in GDB */

    /* Factorial demo */
    int n = (argc > 2) ? atoi(argv[2]) : 5;
    printf("factorial(%d) = %d\n", n, factorial(n));

    /* Pointer demo */
    printf("\n");
    pointer_demo(arr, ARRAY_SIZE);

    /* String demo */
    printf("\n");
    const char *input = (argc > 1) ? argv[1] : "hello";
    string_demo(input);

    printf("\nDone.\n");
    return EXIT_SUCCESS;
}

