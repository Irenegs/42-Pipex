# include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    char *s = envp[2];
    if (argc > 1)
        s = argv[1];
    char **list = ft_super_split(s, ":=");
    int i = 0;
    while (list[i])
    {
        printf("i %d: [%s]\n",i, list[i]);
        i++;
    }
}