#ifndef FILE_H
#define FILE_H

#include <stdio.h>

typedef enum
{
    READ,
    WRITE
} FILEMode;

FILE *FileOpen(const char *filename, const FILEMode mode);
void FileClose(FILE *f);

#endif