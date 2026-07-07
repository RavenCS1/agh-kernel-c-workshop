/*
 * coredump_demo.c
 * ---------------
 * This program intentionally triggers a segmentation fault
 * to demonstrate core dump generation and analysis with GDB.
 *
 * Compile with:
 *   gcc -std=c2x -g -Wall -Wextra coredump_demo.c -o coredump_demo
 *
 * Enable core dumps:
 *   ulimit -c unlimited
 *
 * Run to trigger crash:
 *   ./coredump_demo
 *
 * Analyze with GDB:
 *   coredumpctl -o coredump dump coredump_demo
 *   gdb ./coredump_demo -c coredump
 *   (gdb) bt        <- print backtrace
 *   (gdb) frame 0   <- inspect crash frame
 *   (gdb) info locals
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void level3(int *ptr) {
    /* Intentional null pointer dereference - triggers SIGSEGV */
    *ptr = 42;
}

void level2(int *ptr) {
    level3(ptr);
}

void level1(void) {
    int *ptr = nullptr;  /* null pointer */
    level2(ptr);
}

void buffer_overflow_demo(void) {
    char buf[8];
    /* Writing past the end of the buffer - undefined behavior */
    memset(buf, 'A', 64);
    printf("Buffer: %s\n", buf);
}

int main(int argc, char *argv[argc+1]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [null|overflow]\n", argv[0]);
        fprintf(stderr, "  null     - trigger null pointer dereference\n");
        fprintf(stderr, "  overflow - trigger buffer overflow\n");
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "null") == 0) {
        printf("Triggering null pointer dereference...\n");
        level1();
    } else if (strcmp(argv[1], "overflow") == 0) {
        printf("Triggering buffer overflow...\n");
        buffer_overflow_demo();
    } else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

