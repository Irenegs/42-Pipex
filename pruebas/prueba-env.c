#include "pipex.h"

int main(void)
{
	printf("Puntero environ: %p\n", environ);
	printf("Puntero environ[0] %p\n",  environ[0]);
	printf("String environ[0] %s\n",  environ[0]);
	return (0);
}