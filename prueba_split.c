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
    char **arg;
    int i = 0;
    if (argc != 1)
    {
        printf("s: %d, %s\n", argc, argv[1]);
        arg = envp;//ft_super_split(argv[1], " ");
        while (arg[i])
        {
            printf("%d:%s\n", i, arg[i]);
            i++;
        }
    }
}
