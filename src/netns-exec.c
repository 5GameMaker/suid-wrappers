#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#ifndef IP_BIN_PATH
#define IP_BIN_PATH "/usr/bin/ip"
#endif

#ifndef SUDO_BIN_PATH
#define SUDO_BIN_PATH "/usr/bin/sudo"
#endif

#ifndef ENV_BIN_PATH
#define ENV_BIN_PATH "/usr/bin/env"
#endif

const char *err_not_root = "Not running as root. Please set setuid bit on this executable\n";
const char *err_no_netns = "No namespace specified\n";
const char *err_no_bin = "No binary specified\n";

typedef size_t usize;

int main(int argc, char **argv, char **environ) {
    if (geteuid() != 0) {
        write(STDERR_FILENO, err_not_root, strlen(err_not_root));
        exit(1);
    }
    if (argc < 2) {
        write(STDERR_FILENO, err_no_netns, strlen(err_no_netns));
        exit(1);
    }
    if (argc < 3) {
        write(STDERR_FILENO, err_no_bin, strlen(err_no_bin));
        exit(1);
    }

    usize envcount = 0;
    {
        char *envp = NULL;
        while ((envp = environ[envcount]) != NULL)
            ++envcount;
    }

    char *uid;
    {
        usize len = snprintf(NULL, 0, "#%d", getuid());
        uid = malloc(len + 1);
        snprintf(uid, len + 1, "#%d", getuid());
    }

    char **newargs = malloc(sizeof(const char *) * (8 + envcount + argc - 1));
    const char *s = NULL;
    usize idx = 0;
    #define INS_ST(val) newargs[idx++] = (char *)(val)

    INS_ST(IP_BIN_PATH);
    INS_ST("netns");
    INS_ST("exec");
    INS_ST(argv[1]);
    INS_ST(SUDO_BIN_PATH);
    INS_ST("-u");
    INS_ST(uid);
    INS_ST(ENV_BIN_PATH);

    for (usize i = 0; (s = environ[i++]);)
        INS_ST(s);

    for (usize i = 2; i < argc; i++)
        INS_ST(argv[i]);

    INS_ST(NULL);

    setuid(0);
    execve(IP_BIN_PATH, newargs, environ);
    exit(255);
}
