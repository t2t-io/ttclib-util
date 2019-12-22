#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include "ttclib/util/hexify.h"

int main(int argc, char *argv[]) {
#if 0
    printf("arguments: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("arguments[%d] = %s\n", i, argv[i]);
    }
#endif
    struct stat sb = {0};
    int ret;
    const char *path;

    if (argc < 2) {
        printf("please specify the file to dump in hex\n");
        return 0;
    }

    path = argv[1];
    ret = stat(path, &sb);
    if (ret) {
        switch (ret) {
            case EACCES:        printf("Search permission is denied for one of the directories in the path prefix of %s\n", path); break;
            case ELOOP:         printf("Too many symbolic links encountered while traversing the path: %s\n", path); break;
            case ENAMETOOLONG:  printf("path is too long => %s\n", path); break;
            case ENOENT:        printf("A component of path does not exist, or path is an empty string => %s\n", path); break;
            case ENOMEM:        printf("Out of memory (i.e., kernel memory).\n"); break;
            case EOVERFLOW:     printf("EOVERFLOW\n"); break;
            default:            printf("unknown error (%d) when retrieving file property: %s\n", ret, path); break;
        }
        return ret;
    }

    if (S_IFREG != (sb.st_mode & S_IFMT)) {
        printf("%s is not a regular file\n", path);
        return 1;
    }

    printf("%s with %lld bytes\n", path, sb.st_size);

    printf("0x2F => %s\n", ttlib_util_byte2hex(0x2F, 1));
    printf("0x4A => %s\n", ttlib_util_byte2hex(0x4A, 0));
    return 0;
}
