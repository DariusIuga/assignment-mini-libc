// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <unistd.h>
// For the timespec struct
#include <time.h>

unsigned sleep(unsigned seconds)
{
    // The timespec struct has a seconds field and a nanoseconds field.
    struct timespec req = {seconds, 0};
    struct timespec rem = {0, 0};

    // Invoke the nanosleep syscall with correct arguments.
    int ret = syscall(__NR_nanosleep, &req, &rem);

    // Error checking, as per the man page
    if (ret < 0) {
        if (errno == EINTR) {
            // Sleep was interrupted by a signal.
            return rem.tv_sec;
        } else {
            errno = -ret;
            return -1;
        }
    }

    return 0; // Successfully slept for the requested time.
}

int nanosleep(const struct timespec *req, struct timespec *rem)
{
    // Invoke the nanosleep syscall.
    int ret = syscall(__NR_nanosleep, req, rem);

    // Error checking
    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    return ret;
}
