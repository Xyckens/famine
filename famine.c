#include "famine.h"

bool    check_infection(FILE *fp, const char *string, size_t len)
{
    int ch;
    char buffer[2024];
    size_t buf_index = 0;

    while ((ch = fgetc(fp)) != EOF)
    {
        if (isprint(ch))
            buffer[buf_index++] = ch;
        else 
        {
            if (buf_index >= len)
            {
                buffer[buf_index] = '\0';
                if(strstr(buffer, string))
                {
                    fclose(fp);
                    printf("Already infected.\n");
                    return (true);
                }
            }
            buf_index = 0;
        }
    }
    buffer[buf_index] = '\0';
    if(strstr(buffer, string))
    {
        fclose(fp);
        printf("Already infected.\n");
        return (true);
    }
    return (false);
}

void    infect(FILE *fp, const char *string, size_t len)
{
    fwrite(string, sizeof(char), len, fp);
    printf("INFECT.\n");
    fclose(fp);
}

int main()
{
    FILE *fp = fopen("test", "ab+");
    const char *string = "Famine version 1.0 (c)oded by fvieira-<second-login>";
    size_t len = strlen(string) + 1;
    if (!fp)
    {
        perror("Failed to open file");
        return 1;
    }
    if (!check_infection(fp, string, len))
        infect(fp, string, len);
    
    return 0;
}
