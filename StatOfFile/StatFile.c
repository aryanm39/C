#include <stdio.h>  // for perror(), printf()
#include <sys/stat.h> // for struct stat
#include <fcntl.h> // for open()
#include <sys/sysmacros.h> // for all system macros
#include <time.h> // for ctime()

// global function declarations
int printStatOfFile(char *);

int main(int argc, char **argv, char **envp)
{
	if(argc != 2)
	{
		perror("\n\nENTER A FILE NAME TO PRINT STAT\n\n");
		return(0);
	}

	if(printStatOfFile(argv[1]) != 0)
	{
		perror("\n\nERROR WHILE PRINTING STAT\n\n");
	}

	return(0);
}

int printStatOfFile(char *file)
{
	// local variable declarations
	struct stat fileStat;

	// code
	
	if(stat(file, &fileStat) == -1)
	{
		perror("\n\nERROR WHILE GETTING THE FILE STAT!!!\n\n");
		return(-1);
	}

	printf("\n\nID OF CONTAINING DEVIVE : [%x,%x]\n", 
			major(fileStat.st_dev),
			minor(fileStat.st_dev));

	printf("FILE TYPE : ");

	switch(fileStat.st_mode & S_IFMT) // getting the file Type
	{
		case S_IFBLK:
			printf("BLOCK DEVICE\n");
			break;

		case S_IFCHR:
			printf("CHARACTER DEVICE\n");
			break;

		case S_IFDIR:
			printf("DIRECTORY FILE\n");
			break;
			
		case S_IFIFO:
			printf("FIFO / PIPE FILE\n");
			break;

		case S_IFLNK:
			printf("SYMBOLIC LINK FILE\n");
			break;

		case S_IFREG:
			printf("REGULAR FILE\n");
			break;

		case S_IFSOCK:
			printf("SOCKET FILE\n");
			break;

		default:
			printf("UNKNOWN\n");
	}

	printf("INODE NUMBER : %u\n", fileStat.st_ino);

	printf("MODE : %o\n", fileStat.st_mode);

	printf("LINK COUNT : %u\n", fileStat.st_nlink);

	printf("OWNERSHIP : \n\tUID : %u\t\tGID : %u\n", fileStat.st_uid, fileStat.st_gid);

	printf("PREFERRED I/O BLOCK SIZE : %u bytes\n", fileStat.st_blksize);
	
	printf("FILE SIZE : %u bytes\n", fileStat.st_size);

	printf("BLOCKS ALLOCATED : %u\n", fileStat.st_blocks);

	printf("LAST STATUS CHANGE : %s\n", ctime(&fileStat.st_ctime));

	printf("LAST FILE ACCESS : %s\n", ctime(&fileStat.st_atime));
	
	printf("LAST MODIFIED : %s\n", ctime(&fileStat.st_mtime));

	return(0);
}

