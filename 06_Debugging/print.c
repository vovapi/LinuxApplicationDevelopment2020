#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: ./print 'Hello world!'\n");
        exit(1);
    }

    const int n = strlen(argv[1]);
    char *buf = calloc(n+1, sizeof(char));
    if (buf == NULL) {
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        buf[i] = argv[1][i];
    }

    printf("%s\n", buf);

    free(buf);
    free(buf);

    return 0;
}