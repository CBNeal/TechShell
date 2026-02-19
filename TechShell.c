// Name(s): Callum Neal, Madison Slayden, Jack Tomlin
// Description: BASH clone in C
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>


#define BUFFER 1024

struct ShellCommand{
	char *command;
	char *args[256];
	int argc;
	int redirect; // using an int instead of Bool cause I couldn't get it to work so 0 or 1
	char redirectType; // Should only ever be < or > 
	char *redirectFile; 
};

//////// Some function ideas: ////////////

void displayPrompt()
{
	char cwd[BUFFER];
	getcwd(cwd, sizeof(cwd));
	printf("%s$", cwd);
}

void getInput(char *input, size_t size)
{
    fgets(input, size, stdin);
    input[strcspn(input, "\n")] = '\0'; 
}


struct ShellCommand parseInput(char *input)
{
	const char s[2] = " ";
	char *token;
	int index = 0;
	struct ShellCommand command;

	// I have to init the Command Structs
	command.argc = 0;
	command.redirect = 0;
	command.redirectType = '\0';
	command.redirectFile = NULL;
	command.command = NULL;



	token = strtok(input,s);

	while (token != NULL && index < 20)
	{
		if(strcmp(token, ">") == 0 || strcmp(token, "<") == 0)
		{
			command.redirect = 1;
			command.redirectType = token[0];

			token = strtok(NULL, s);
			command.redirectFile = token;
			token = strtok(NULL, s);
		}
		else{
		command.args[index] = token;
		index++;

		token = strtok(NULL, s);
		}
	}
	command.args[index] = NULL;
	command.argc = index;
	command.command = command.args[0];

	return command;
}




		
void executeCommand(struct ShellCommand command)
{
    if (command.command == NULL)
        return;

    if (strcmp(command.command, "cd") == 0)
    {
        if (command.args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else if (chdir(command.args[1]) == -1)
        {
            perror("cd failed");
        }
        return;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
		if (command.redirect && command.redirectType == '>')
		{
    		int fd = open(command.redirectFile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    		if (fd < 0)
    		{
        		perror("open failed");
        		exit(1);
    		}

    		dup2(fd, STDOUT_FILENO);
    		close(fd);
		}

		if (command.redirect && command.redirectType == '<')
        {
            int fd = open(command.redirectFile, O_RDONLY);
            if (fd < 0)
            {
                perror("open failed");
                exit(1);
            }

            // Replace stdin with file
            if (dup2(fd, STDIN_FILENO) < 0)
            {
                perror("dup2 failed");
                close(fd);
                exit(1);
            }

            close(fd);  // not needed anymore
        }

        execvp(command.command, command.args);

        perror("exec failed");
        exit(1);
    }
    else
    {
        wait(NULL);
    }
}

int main() // MAIN
{
	char input[256];
	struct ShellCommand command;
		
	// repeatedly prompt the user for input
	for (;;)
	{
        // display the prompt
        displayPrompt();

	    // get the user's input
	    getInput(input, sizeof(input));
	    
	    // parse the command line
	    command = parseInput(input);
	    
	    // execute the command
	    executeCommand(command);
	    
	}

	exit(0);
}

