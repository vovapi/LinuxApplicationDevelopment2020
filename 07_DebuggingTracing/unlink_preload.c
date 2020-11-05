#define _GNU_SOURCE
#include <dlfcn.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

typedef int (*unlinkat_syscall_t)(int, const char*, int);
typedef int (*unlink_syscall_t)(const char*);

int unlinkat(int fd, const char* pathname, int flag) {
    char *path = strdup(pathname);
    if (strstr(basename(path), "FIX")) {
        errno = EPERM;
        return -1;
    }
    free(path);
    return ((unlinkat_syscall_t)dlsym(RTLD_NEXT, "unlinkat"))(fd, pathname, flag);
}

int unlink(const char* pathname) {
    char *path = strdup(pathname);
    if (strstr(basename(path), "FIX")) {
        errno = EPERM;
        return -1;
    }
    free(path);
    return ((unlink_syscall_t)dlsym(RTLD_NEXT, "unlink"))(pathname);
}
