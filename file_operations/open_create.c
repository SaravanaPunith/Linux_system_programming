/*
 ============================================================================
 Description : understanding open vs create
 ============================================================================
 */
/*
 * creat()
       creat()    is    equivalent    to    open()   with   flags   equal   to
       O_CREAT|O_WRONLY|O_TRUNC.
 * 
 * Question is :
 * what happens we create and then open with O_WRONLY ? will it return same fd??
 * 
 */ 
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
 
#define BUF_SIZE 8192
 
int main(int argc, char* argv[]) 
{
    int open_fd = 0;
    char buffer[BUF_SIZE] = {0};      /* Character buffer */
    ssize_t ret_out = 0;  /* Number of bytes returned by read() and write() */
    int create_fd = 0;
 
    create_fd = creat (argv [1], O_CREAT);
    if (create_fd == -1) {
            perror ("open");
            return 2;
    }
    printf ("create_fd : %d\n", create_fd);

    /* Create input file descriptor */
    open_fd = open (argv[1], O_WRONLY );
    if (open_fd == -1) {
            perror ("open");
            return 2;
    }
    printf ("open_fd : %d\n", open_fd);
 
    // using open_fd here
    memset (buffer, 'A', sizeof(buffer));
    ret_out = write (open_fd, &buffer, (ssize_t) sizeof(buffer));
    if (ret_out == -1) {
        /* Write error */
        perror("write");
        return 4;
    }

    // using create_fd here   
    memset (buffer, 'B', sizeof(buffer));
    ret_out = write (create_fd, &buffer, (ssize_t) sizeof(buffer));
    if (ret_out == -1) {
        /* Write error */
        perror("write");
        return 5;
    }
 
    /* Close file descriptors */
    close (open_fd);
    close (create_fd);
 
    return (EXIT_SUCCESS);
}

