#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef int (* func)(int, const char *, int);

int unlinkat(int dirfd, const char *pathname, int flags)
{
    if (strstr(pathname, "FIX"))
        return EPERM;
    func old_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
    return old_unlinkat(dirfd, pathname, flags);
}
