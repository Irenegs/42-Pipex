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


int main(int argc, char **argv)//, char **envp)
{
    printf("argc: %d\n", argc);
    //if (argc > 1)
        char *s = argv[1];
    //else
    //    char *s = envp[2];
    printf("arg: %s\n", argv[1]);
    char **list = ft_super_split(s, " ");
    int i = 0;
    while (list[i])
    {
        printf("i %d: [%s]\n",i, list[i]);
        i++;
    }
    ft_out(list, i);
}
