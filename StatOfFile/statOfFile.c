#include <stdio.h>  
#include <sys/stat.h>  
#include <fcntl.h>  

// Function declaration
int printFileInfo(char *);

int main(int argc, char **argv) {
    if (argc != 2) {
        perror("\n\nENTER A FILE NAME TO CHECK TYPE AND PERMISSIONS\n\n");
        return 1;
    }

    if (printFileInfo(argv[1]) != 0) {
        perror("\n\nERROR WHILE GETTING FILE INFO\n\n");
        return 1;
    }

    return 0;
}

int printFileInfo(char *file) {
    struct stat fileStat;

    // Get file status
    if (stat(file, &fileStat) == -1) {
        perror("\n\nERROR WHILE GETTING THE FILE STAT!!!\n\n");
        return -1;
    }

    // Check file type
    printf("FILE TYPE: ");
    switch (fileStat.st_mode & S_IFMT) {
        case S_IFBLK:  printf("BLOCK DEVICE\n"); break;
        case S_IFCHR:  printf("CHARACTER DEVICE\n"); break;
        case S_IFDIR:  printf("DIRECTORY FILE\n"); break;
        case S_IFIFO:  printf("FIFO / PIPE FILE\n"); break;
        case S_IFLNK:  printf("SYMBOLIC LINK FILE\n"); break;
        case S_IFREG:  printf("REGULAR FILE\n"); break;
        case S_IFSOCK: printf("SOCKET FILE\n"); break;
        default:       printf("UNKNOWN\n");
    }

    // Print file permissions
    printf("FILE PERMISSIONS: ");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\n");

    return 0;
}
