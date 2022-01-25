#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fd = open("files/42_no_nl", O_RDONLY);
    int i = 0;
    char *nl;

    while (i < 10)
    {
        nl = get_next_line(fd);
        printf("gnl:%s", nl);
        i++;
    }
    close (fd);
}
