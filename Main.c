#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>

#define BUFFER 1024

int main()
{

	char cwd[BUFFER];
	getcwd(cwd, sizeof(cwd));
	printf("%s", cwd);

	return 0;
}
