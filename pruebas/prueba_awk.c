# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>

int len_next_word(char const *s, char *sep, int pos);

int main(void)//int argc, char **argv)
{
    char *arg[6] = {"awk", "-F", " ", "{print $1}", "a.txt", NULL};
    execve("uug", arg, environ);
    perror(NULL);
    return (0);
}