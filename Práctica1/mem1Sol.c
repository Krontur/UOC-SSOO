
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>

struct {
    char input[8];
    char test[8];
} data;

int main(int argc, char *argv[])
{

    sprintf(data.test, "uoc");

    do
    {

	    printf("Passwd? ");
	    scanf(" %7s", data.input);
	    __fpurge(stdin);

    }
    while (strcmp(data.input, data.test) != 0);

    printf("Passwd OK\n");
    return(0);
}

