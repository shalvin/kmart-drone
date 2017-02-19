#include "commands.h"
#include <stdlib.h>
#include <stdio.h>

void cmdGo(int argc, const char** args)
{
    printf("gone\n");
    return;
}


void cmdExit(int argc, const char** args)
{
    exit(0);
}
