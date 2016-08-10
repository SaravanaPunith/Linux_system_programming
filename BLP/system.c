#include <stdlib.h>
#include <stdio.h>

int main()
{
        printf("start\n");
        // inefficient - invokes program using a new shell
        system ("ps ax &");
        printf("stop\n");
        return 0;
}
