// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <stdlib.h>
#include <string.h>

int puts(const char *s)
{
    size_t len = strlen(s);

    // Create a buffer to hold the string and the newline character.
    char *buffer = (char *)malloc(len + 1);
    strcpy(buffer, s);
    buffer[len] = '\n';

    // Write the combined string to stdout (file descriptor 1).
    int ret = syscall(__NR_write, 1, buffer, len + 1);

    if (ret < 0) {
        errno = -ret;
        return -1; // Return -1 on error.
    }

    return ret;
}
