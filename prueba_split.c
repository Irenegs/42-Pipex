# include "pipex.h"
/*
int main(void)
{
    printf("'%d\n", '\'');
    printf("\"%d\n", '"');
    printf("compare %d\n", '\'' == '"');
    printf("compare %d\n", 2 == 3);
}
*/


int main(int argc, char **argv, char **envp)
{
    char *s = envp[2];
    if (argc > 1)
        s = argv[3];
    printf("arg: %s\n", argv[3]);
    char **list = ft_super_split(s, " ");
    int i = 0;
    while (list[i])
    {
        printf("i %d: [%s]\n",i, list[i]);
        i++;
    }
}
