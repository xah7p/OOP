#include "file.h"

FILE *FileOpen(IN const char *filename, IN const FILEMode mode)
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

void FileClose(IN FILE *f)
{
    fclose(f);
}