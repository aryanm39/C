#include <stdio.h> // for perror(), printf()
#include <fcntl.h> // for open()
#include <unistd.h> // for dup()

int outputRedirect(char *);	// global function declarations

int main(int argc, char **argv, char **envp)
{
	if(argc != 2)	{
		perror("PLEASE PROVIDE OUTPUT REDIRECTION FILE NAME !!!\n");
		return(0);
	}

	if(outputRedirect(argv[1]) != 0)	{
		perror("ERROR WHILE OUTPUT REDIRECT !!!\n\n");
		return(0);
	}

	return(0);
}

int outputRedirect(char *oFile)
{
	int fdOut = 0;
	//if( (fdOut = open(oFile, O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1 )
	if( !(fdOut = open(oFile, O_WRONLY | O_CREAT | O_TRUNC), 0666) )
	{
		perror("ERROR WHILE OPENING OUTPUT FILE !!!\n");
		return(-1);
	}

	// close stdout file as we want to write output into a file
	close(1);
	// using dup() copy the UFDT of our file into first free UFDT entry i.e at location of stdout UFDT entry
	dup(fdOut);
	printf("This is the Output That will redirected To a File\n");
	close(fdOut);
	return(0);
}
