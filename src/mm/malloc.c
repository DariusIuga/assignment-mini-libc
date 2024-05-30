// SPDX-License-Identifier: BSD-3-Clause

#include <internal/essentials.h>
#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

void *malloc(size_t size)
{
    struct mem_list *mem = mmap(NULL, size + sizeof(struct mem_list),
                                PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        return NULL;
    }

    mem->len = size;
    // Return a pointer immediately after the mem_list struct.
    return (void *)(mem + 1);
}

void *calloc(size_t nmemb, size_t size)
{
    return malloc(nmemb * size);
}

void free(void *ptr)
{
    if (ptr != NULL) {
        // Get the pointer to the allocated region, including the struct header.
        struct mem_list *mem = (struct mem_list *)ptr - 1;
        munmap(mem, mem->len + sizeof(struct mem_list));
    }
}

void *realloc(void *ptr, size_t size)
{
    if (ptr != NULL) {
        ptr = malloc(size);
    }
    return ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
    return realloc(ptr, nmemb * size);
}
