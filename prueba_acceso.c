
# include "pipex.h"

int main(void)
{
    printf("%d\n", access("/usr/bin/wc", F_OK));
    printf("%d\n", access("/usr/bin/wc", X_OK));
}