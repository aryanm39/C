#include <stdio.h> // for perror(), printf()
#include <fcntl.h> // for open()
#include <unistd.h> // for dup()

int inputRedirect(char *);	// function declarations

int main(int argc, char **argv, char **envp)
{
	if(argc != 2)	{
		perror("PLEASE GIVE A FILE NAME FOR INPUT REDIRECTION\n\n");
		return(0);
	}

	if(inputRedirect(argv[1]) != 0)	{
		perror("ERROR WHILE INPUT REDIRECTION !!!\n\n");
		return(0);
	}
	return(0);
}

int inputRedirect(char *iFile)	{
	int fd = 0;
	char buffer[20] = { '\0' };
	int numberOfCharRead = 0;
	int numberOne = 0;
	int numberTwo = 0;
	//if( (fd = open(iFile, O_RDONLY)) == -1 )
	if( !(fd = open(iFile, O_RDONLY)))	{
		perror("ERROR WHILE OPENING THE FILE !!!\n\n");
		return(-1);
	}
	// close the stdin for input redirection
	close(0); // first index of UFDT is our stdin file that will close
	dup(fd); // this line will duplicate UFDT entry in first free entry in UFDT we freed the first entry.

	// scanf will take input from our file as scanf() uses first index of UFDT to read The Data
	scanf("%d", &numberOne);
	scanf("%d", &numberTwo);

	printf("numberOne From File : %d\n", numberOne);
	printf("numberTwo From File : %d\n", numberTwo);
	printf("\n%d + %d = %d\n", numberOne, numberTwo, numberOne + numberTwo);
	close(fd);
	return(0);
}

