#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/uio.h>

static char filename[] = "/tmp/preadv-XXXXXX";
static char outbuf[11] = "0123456789";
static char inbuf[11]  = "----------";

static struct iovec ovec[2] = {{
        .iov_base = outbuf + 5,
        .iov_len  = 5,
    },{
        .iov_base = outbuf + 0,
        .iov_len  = 5,
    }};

static struct iovec ivec[3] = {{
        .iov_base = inbuf + 6,
        .iov_len  = 2,
    },{
        .iov_base = inbuf + 4,
        .iov_len  = 2,
    },{
        .iov_base = inbuf + 2,
        .iov_len  = 2,
    }};

void cleanup(void)
{
    unlink(filename);
}

int main(int argc, char **argv)
{
    int fd, rc;

    fd = mkstemp(filename);
    if (-1 == fd) {
        perror("mkstemp");
        exit(1);
    }
    atexit(cleanup);

    /* write to file: "56789-01234" */
    rc = pwritev(fd, ovec, 2, 0);
    if (rc < 0) {
        perror("pwritev");
        exit(1);
    }

    /* read from file: "78-90-12" */
                             // start from offset 2 
    rc = preadv(fd, ivec, 3, 2);
    if (rc < 0) {
        perror("preadv");
        exit(1);
    }

    printf("result  : %s\n", inbuf);
    printf("expected: %s\n", "--129078--");
    return 0;
} 
