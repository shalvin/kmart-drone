#include "shellinput.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

const char** commandWords = {
    "reset",
    "go",
};


static char* ReadLine()
{
    uint32_t bufferSize = BUFFER_SIZE * sizeof(char);
    char* buffer = malloc(bufferSize);
    uint32_t position = 0; 
    while (true)
    {
        int32_t c = getchar();
        if (c == '\n' || c == EOF)
        {
            // Terminate at a newline or end of file
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position++] = c;

        if (position >= bufferSize)
        {
            bufferSize += BUFFER_SIZE;
            buffer = realloc(buffer, bufferSize);
        }
    }
}


static char** SplitLine(const char* line, uint32_t lineLen)
{

}


void ShellInputLoop()
{
    char* line = ReadLine();

    free(line);
}
