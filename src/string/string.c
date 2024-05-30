// SPDX-License-Identifier: BSD-3-Clause

#include <stdlib.h>
#include <string.h>

char *strcpy(char *destination, const char *source)
{
    size_t i;
    for (i = 0; i < strlen(source); i++) {
        destination[i] = source[i];
    }
    destination[i] = '\0';
    return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
    for (size_t i = 0; i < len; i++) {
        destination[i] = source[i];
    }
    return destination;
}

char *strcat(char *destination, const char *source)
{
    unsigned int len = strlen(destination), i;
    for (i = 0; i < strlen(source); i++) {
        destination[len + i] = source[i];
    }
    destination[len + i] = '\0';
    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
    unsigned int dest_len = strlen(destination), i;
    for (i = 0; i < len && source[i] != '\0'; i++) {
        destination[dest_len + i] = source[i];
    }
    destination[dest_len + i] = '\0';
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
    for (unsigned int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return strlen(str1) - strlen(str2);
}

int strncmp(const char *str1, const char *str2, size_t len)
{
    for (unsigned int i = 0; str1[i] != '\0' && i < len; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

size_t strlen(const char *str)
{
    size_t i = 0;

    for (; *str != '\0'; str++, i++)
        ;

    return i;
}

char *strchr(const char *str, int c)
{
    c = (char)c;
    for (unsigned int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            return (char *)(str + i);
        }
    }
    return NULL;
}

char *strrchr(const char *str, int c)
{
    c = (char)c;
    for (int i = strlen(str) - 1; i >= 0; i--) {
        if (str[i] == c) {
            return (char *)(str + i);
        }
    }
    return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
    const char *a = haystack, *b = needle;
    while (1) {
        if (!*b) {
            // First instance of the needle is found
            return (char *)haystack;
        }
        if (!*a) {
            // The haystack was traversed, but the needle wasn't found
            return NULL;
        }
        if (*a++ != *b++) {
            // The first letters in the searched string and the source string
            // are different
            a = ++haystack;
            b = needle;
        }
    }

    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
    char *last_match = NULL;

    while (1) {
        char *current = strstr(haystack, needle);
        if (!current) {
            return last_match;
        }
        last_match = current;
        haystack = current + 1;
    }
}

void *memcpy(void *destination, const void *source, size_t num)
{
    unsigned char *dest_copy = (unsigned char *)destination;
    const unsigned char *src_copy = (const unsigned char *)source;
    for (size_t i = 0; i < num; i++) {
        dest_copy[i] = src_copy[i];
    }

    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
    // If the destination buffer starts before the source, we copy forwards,
    // using memcpy
    if (destination < source) {
        return memcpy(destination, source, num);
    }

    // If the destination starts after the source, we will copy backwards
    unsigned char *dest_copy = (unsigned char *)destination;
    const unsigned char *src_copy = (const unsigned char *)source;
    for (int i = num - 1; i >= 0; i--) {
        dest_copy[i] = src_copy[i];
    }

    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
    const char *str1 = (const char *)ptr1, *str2 = (const char *)ptr2;
    for (size_t i = 0; i < num; i++) {
        if (str1[i] != str2[i]) {
            return str1[i] - str2[i];
        }
    }
    return 0;
}

void *memset(void *source, int value, size_t num)
{
    value = (unsigned char)value;
    unsigned char *copy = (unsigned char *)source;

    for (size_t i = 0; i < num; i++) {
        copy[i] = value;
    }
    return source;
}
