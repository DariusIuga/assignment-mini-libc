// SPDX-License-Identifier: BSD-3-Clause

#include <errno.h>
#include <internal/syscall.h>
#include <sys/mman.h>
// For NULL
#include <stdio.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
    // Invoke the mmap syscall.
    void *ret = (void *)syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    // Error checking
    if (fd > 2 && !(flags & MAP_ANONYMOUS)) {
        errno = EBADF;
        ret = MAP_FAILED;
    } else if (!((flags & MAP_PRIVATE) || (flags & MAP_SHARED))) {
        errno = EINVAL;
        ret = MAP_FAILED;
    }

    return ret;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
    // Invoke the mremap syscall.
    void *ret = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);

    // Check for errors.
    return ret;
}

int munmap(void *addr, size_t length)
{
    // Invoke the munmap syscall.
    int ret = syscall(__NR_munmap, addr, length);

    // Check for errors.
    if (ret < 0) {
        errno = EINVAL;
        return -1;
    }
    return 0;
}
