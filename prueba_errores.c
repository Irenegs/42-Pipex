
# include "pipex.h"
# include <sys/wait.h>
# include <sys/types.h>
#include <errno.h>
 #include <signal.h>
int main(int argc, char **argv)
{
    
    int i= 0;
    while (i < 108)
    {
        psignal(i, NULL);
        i++;
    }
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