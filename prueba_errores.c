
# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>
#include <errno.h>
 #include <signal.h>
int main(void)//int argc, char **argv)
{
    printf("Error de lectura\n");
    open("z.txt", O_RDONLY);
    perror(NULL);
    printf("Error de lectura\n");
    open("z.txt", O_RDONLY);
    perror(NULL);
    printf("Prueba de permisos de ejecución\n");
    execve("./a.txt",NULL, environ);
    perror(NULL);
    printf("Prueba de no existencia del comando\n");
    execve("asf",NULL, environ);
    perror(NULL);
    exit(0);
    /*
    i=127;
    printf("%d:%s\n", i, strerror(i));
    return (0);
    if (argc != 1)
    {
        if (access(argv[1], F_OK) == 0)
        {
            if (access(argv[1], X_OK) == 0)
                return (0);
        }
        printf("%s", strerror(errno));
    }
    return(1);*/
}