# include "pipex.h"

int main(int argc, char **argv, char **envp)
{
    if (argc != 0 && argv)
        printf("hola\n");
    printf("argv[3]: %s\n", argv[3]);
    //char *argum[4] = {"ls", "-l", "-a", NULL};
    //execve("/bin/ls", argum, envp);
    char *argum1[4] = {"awk", "/b/", "b.txt", NULL};
    execve("/usr/bin/awk", argum1, envp);
}