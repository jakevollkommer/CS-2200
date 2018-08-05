#pragma once

#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Simulates a kernel panic by printing a message and then immediately killing the simulation.
 */
static inline void panic(const char *message) {
    if (message != NULL)
        printf("panic: %s\n", message);
    exit(EXIT_FAILURE);
}
