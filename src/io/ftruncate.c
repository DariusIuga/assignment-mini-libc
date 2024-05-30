// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>

int ftruncate(int fd, off_t length)
{
    // Invoke the ftruncate sycall
    int ret = syscall(__NR_ftruncate, fd, length);

    // Error checking.
    if (ret < 0) {
        errno = -ret;
        ret = -1;
    }

    return ret;
}
