#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define usize size_t

int main(int argc, char **argv) {
    clearenv();

    if (argc >= 1 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
        printf("Usage: %s [NETNS] cmd ...\n", argv[0]);
        return 1;
    }

    char **args = (char**) malloc((argc + 3) * sizeof(char*));
    args[0] = argv[0];
    args[1] = "netns";
    args[2] = "exec";
    args[argc + 2] = NULL;
    for (usize i = 1; i < argc; i++) {
        args[i + 2] = argv[i];
    }

    execve("/usr/bin/ip", args, NULL);
}
