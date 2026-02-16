// Name(s):
// Description:
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER 1024

struct ShellCommand{
	char *command[256];
	char *args[256];
	int argc;
	int redirect = 0;
	char redirectType = NULL;
	char *redirectFile = NULL:
}

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
}


struct ShellCommand parseCommand(char *input)
{
	cost char s[2] = " ";
	char *token;
	char *words[20];
	int index = 0;
	ShellCommand command;


	token = strtok(str,s);

	while (token != NULL && index < 20)
	{
		if(strcmp(token, ">") || strcmp(token, "<"))
		{
			command.redirect = 1;
			command.redirectType = token;

			token = strtok(NULL, s);
			command.redirectFIle = token;
			token = strtok(NULL, s);
		}
		words[index] = token;
		index++;

		token = strtok(NULL, s);
	}
	command.argc = index;
	command.args = words;

	for (int n = 0; n < index; n++)
	{
		printf("word %d: %s\n", n, words[n]);
	}



		
/*
    A function that parses through the user input.
    Consider having this function return a struct that stores vital
    information about the parsed instruction such as:
    - The command itself
    - The arguments that come after the command 
        Hint: When formatting your data, 
        look into execvp and how it takes in args.
    - Information about if a redirect was detected such as >, <, or |
    - Information about whether or not a new file 
        needs to be created and what that filename may be.
    

    Some helpful functions when doing this come from string.h and stdlib.h, such as
    strtok, strcmp, strcpy, calloc, malloc, realloc, free, and more

    Be sure to consider/test for situations when a backslash is used to escape the space char
    and when quotes are used to group together various tokens.
*/

/*
    A function that executes the command. 
    This function might take in a struct that represents the shell command.

    Be sure to consider each of the following:
    1. The execvp() function. 
        This can execute commands that already exist, that is, 
        you don't need to recreate the functionality of 
        the commands on your computer, just the shell.
        Keep in mind that execvp takes over the current process.
    2. The fork() function. 
        This can create a process for execvp to take over.
    3. cd is not a command like ls and mkdir. 
        cd is a toold provided by the shell, 
        so you WILL need to recreate the functionality of cd.
    4. Be sure to handle standard output redirect and standard input redirects here 
        That is, there symbols: > and <. 
        Pipe isn't required but could be a nice addition.
*/


int main() // MAIN
{
	char input[256];

/*	struct ShellCommand command;
		
	// repeatedly prompt the user for input
	for (;;)
	{
        // display the prompt
        displayPrompt();

	    // get the user's input
	    input = getInput();
	    
	    // parse the command line
	    command = parseInput(input);
	    
	    // execute the command
	    executeCommand(command);
	}
*/
	printPrompt();
	getInput(input, sizeof(input));
	parseCommand(input);
	exit(0);
}

