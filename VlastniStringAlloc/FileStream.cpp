#include "FileStream.h"
#include "CustomMacros.h"
#include <iostream>
#include <fstream>

char* FileStream::ReadAllText(char* filePath)
{
    // Alocate per 500 bytes. 
    // With each 501th character allocate another 500.
    // After reading is done, resize the pointer to string's length

    char* buffer = (char*)allocate_heap_clean(500, 1);

    return nullptr;
}

char** FileStream::ReadAllLines(char* filePath)
{
    // Alocate per 500 bytes for each line. 
    // With each 501th character allocate another 500 to the line.
    // After reading is done, resize the pointer to file line according to string's length
    // Always allocate one line by one. Next line = alloc += 1;

    return nullptr;
}

void FileStream::WriteAllText(char* filePath, char* text)
{

}

void FileStream::WriteAllLines(char* filePath, char** content)
{

}
