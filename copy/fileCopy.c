#include <stdio.h> // for perror(), printf()
#include <fcntl.h> // for open()
#include <unistd.h> // for read(), write()

// global function declarations
int copyFile(char *, char *);

int main(int argc, char **argv)
{
	// check whether user giving poroper input
	if(argc != 3)
	{
		perror("\n\nPLEASE GIVE TWO FILE NAMES AS COMMAND LINE ARGUMENTS !!!\n\n");
		return(0);
	}

	if(copyFile(argv[1], argv[2]) == 0)
	{
		printf("\n\nFILE COPY SUCCESSFULLY\n\n");
	}
	else
	{
		printf("\n\nFAILD TO COPY FILE !!!\n\n");
	}

	return(0);
}

int copyFile(char *fileOne, char *fileTwo)
{
	// local variable declarations
	int fdOne = 0;
	int fdTwo = 0;
	int numberOfCharRead = 0;

	char buffer[20] = { '\0' };

	if(!(fdOne = open(fileOne, O_RDONLY)))
	{
		perror("\n\nERROR WHILE OPENING FILE ONE !!!\n\n");
		return(-1);
	}

	if(!(fdTwo = open(fileTwo, O_WRONLY | O_CREAT | O_TRUNC, 0666)))
	{
		perror("\n\nERROR WHILE OPENING FILE TWO !!!\n\n");
		return(-2);
	}

	while( numberOfCharRead = read(fdOne, buffer, sizeof(buffer)) )
	{
		write(fdTwo, buffer, numberOfCharRead);
	}

	if(numberOfCharRead == -1)
	{
		perror("\n\nERROR WHILE READING FILE !!!\n\n");
		return(-3);
	}

	close(fdOne);
	close(fdTwo);

	return(0);
}
