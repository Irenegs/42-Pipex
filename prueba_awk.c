# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>

int len_next_word(char const *s, char *sep, int pos);

int main(void)//int argc, char **argv)
{
    char *arg[6] = {"awk", "-F;", "{print $1}", "a.txt", NULL};
    execve("sfk", arg, environ);
    perror(NULL);
    /*
    char **arg;
    int i = 0;
    if (argc != 1)
    {
        printf("s: %s\n", argv[1]);
        arg = ft_super_split(argv[1], " ");
        while (arg[i])
        {
            printf("%d:%s\n", i, arg[i]);
            i++;
        }
    }*/
    return (0);
}