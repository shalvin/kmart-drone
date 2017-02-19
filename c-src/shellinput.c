#include "shellinput.h"
#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define ARRAYSIZE(a) (sizeof(a) / sizeof(a[0]))

#define BUFFER_SIZE 1024


static char* read_line()
{
    int bufferSize = BUFFER_SIZE * sizeof(char);
    char* buffer = (char*)malloc(bufferSize);
    int position = 0; 
    while (true)
    {
        int c = getchar();
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


void split_line(const char* line, char*** outList, int* outSize)
{
    int capacity = 4;
    int index = 0;
    char** splitList = malloc(capacity * sizeof(char*));

    // Create a non-const copy of line
    int lineLen = strlen(line);
    char* tmpLine = (char*)malloc((lineLen + 1) * sizeof(char));
    strncpy(tmpLine, line, lineLen);

    char* token = strtok(tmpLine, " ");
    while (token)
    {
        if (index >= capacity)
        {
            capacity = capacity * 2 + 4;
            splitList = (char**)realloc(splitList, capacity);
        }
        int tokenLen = strlen(token);
        splitList[index] = (char*)malloc((tokenLen + 1) * sizeof(char)); // +1 for null term
        strncpy(splitList[index], token, tokenLen);
        splitList[index][tokenLen + 1] = '\0';
        token = strtok(NULL, " ");
        index++;
    }
    *outList = splitList;
    *outSize = index;
}


void free_split_lines(char** list, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(list[i]);
    }
    free(list);
}


void parse_line(char** args, int argsSize)
{
    if (argsSize <= 0)
    {
        return;
    }

    const char* command = args[0];
    for (int i = 0; i < ARRAYSIZE(commandWords); i++)
    {
        if (strcmp(command, commandWords[i]) == 0)
        {
            (commandFunctions[i])(argsSize - 1, (const char**)(args + 1));
        }
    }
}


void shell_read_line_loop()
{
    while (true)
    {
        printf("> ");
        char* line = read_line();

        char** splitLineList;
        int splitLineSize;
        split_line(line, &splitLineList, &splitLineSize);

        parse_line(splitLineList, splitLineSize);

        free_split_lines(splitLineList, splitLineSize);

        free(line);
    }
}
