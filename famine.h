#ifndef FAMINE_H
# define FAMINE_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <ctype.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <unistd.h>
# include <elf.h>

void    infect(FILE *fp, const char *string, size_t len);
bool    check_infection(FILE *fp, const char *string, size_t len);
bool    check_elf(FILE *fp, int arch);
void    analyze_directory(const char *dirname, const char *string, size_t len);
void    run_infection();

#endif