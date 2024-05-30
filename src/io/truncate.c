// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>

int truncate(const char *path, off_t length)
{
    // Invoke the truncate sycall
    int ret = syscall(__NR_truncate, path, length);

    // Error checking.
    if (ret < 0) {
        errno = -ret;
        ret = -1;
    }

    return ret;
}
