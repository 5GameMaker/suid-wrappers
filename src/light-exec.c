#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv) {
    clearenv();
    execve("/usr/bin/light", argv, NULL);
}
