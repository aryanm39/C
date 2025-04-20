#include <stdio.h> // for perror() printf()
#include <fcntl.h> // for open()
#include <unistd.h> // for read(), write()

// global function declarations
int printEveryNthChar(char *, int); // fileName, nth position

int main(int argc, char **argv, char *envp[])
{
	int position = 0;

	if(argc != 2)
	{
		perror("PLEASE GIVE INPUT FILE AS COMMAND LINE ARUMENT\n");
		return(0);
	}

	printf("\n\nENTER THE NTH POSITION : ");
	scanf("%d", &position);

	if(printEveryNthChar(argv[1], position) != 0)
	{
		perror("ERROR WHILE PRINTING THE Nth CHAR OF FILE !!!\n");
	}

	return(0);
}

int printEveryNthChar(char *file, int offset)
{
	// local variable declarations
	int fd = 0;
	int numberOfCharRead = 0;
	char character = '\0';

	// code
	if(!(fd = open(file, O_RDONLY)))
	{
		perror("ERROR WHILE OPENING THE FILE !!!\n");
		return(-1);
	}

	lseek(fd, offset, SEEK_SET);

	while(1)
	{
		numberOfCharRead = read(fd, &character, sizeof(character));

		if(numberOfCharRead <= 0)
		{
			break;
		}
		lseek(fd, offset, SEEK_CUR);	
		printf("%c", character);
	}
	
	if(numberOfCharRead == -1)
	{
		perror("ERROR WHILE READING FILE !!!\n");
		return(-2);
	}

	printf("\n\n");

	return(0);	
}

