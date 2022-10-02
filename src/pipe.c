#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

const char *fifo_path = "./fifo-test";

char *pipe_next()
{
    char *msg = malloc(80);
    int fd = open(fifo_path, O_RDONLY);
    read(fd, msg, sizeof(msg));
    close(fd);
    return msg;
}

int main()
{
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    mkfifo(fifo_path, 0666);

    while (1)
    {
        char *msg = pipe_next();
        // Print the read message
        printf("SBCL: %s\n", msg);
        sleep(1/60);
    }
    return 0;
}
