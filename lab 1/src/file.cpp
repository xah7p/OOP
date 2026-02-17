#include "file.h"

FILE *FileOpen(const char *filename, FILEMode mode)
{   
    FILE *f = NULL;
    if (filename)
    {
        switch (mode)
        {
        case READ:
            f = fopen(filename, "r");
            break;
        case WRITE:
            f = fopen(filename, "w");
            break;
        }
    }
    return f;
}

void FileClose(FILE *f)
{
    fclose(f);
}