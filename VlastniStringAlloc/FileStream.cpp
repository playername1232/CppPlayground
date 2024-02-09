#include "FileStream.h"
#include "CustomMacros.h"
#include <iostream>
#include <fstream>

char* FileStream::ReadAllText(const char* filePath)
{
    // Alocate per 500 bytes. 
    // With each 501th character allocate another 500.
    // After reading is done, resize the pointer to string's length

    size_t allocSize = 500;
    char* buffer = (char*)allocate_heap_clean(allocSize, 1);
    size_t buffIdx = 0;

    FILE* file; 
    fopen_s(&file, filePath, "r");

    if (file == nullptr)
        return nullptr;

    while (!feof(file))
    {
        if (allocSize - 1 == buffIdx)
        {
            allocSize += 500;

            buffer = (char*)reallocate_heap_block(buffer, allocSize, 1);
        }

        fread(buffer, 1, 1, file);
        buffIdx += 1;
    }

    if (buffer[buffIdx] != '\0') // If last character read from file isn't null terminator
    {
        if (buffIdx + 1 == allocSize)
            buffer = (char*)reallocate_heap_block(buffer, allocSize + 1, 1);

        buffer[buffIdx + 1] = '\0'; // Add null terminator to last index
        buffIdx += 1;
    }

    buffer = (char*)reallocate_heap_block(buffer, buffIdx + 1, 1);

    return buffer;
    

    /*FILE* file;
    fopen_s(&file, filePath, "wr+");

    if (file == nullptr)
        return nullptr;

    int allocSize = fgetc(file);

    char* buffer = (char*)allocate_heap_clean(allocSize, 1);

    fread(buffer, 1, allocSize, file);

    fclose(file);

    if (buffer[allocSize - 1] != '\0')
    {
        buffer = (char*)reallocate_heap_block(buffer, allocSize + 1, 1);

        buffer[allocSize] = '\0';
    }

    return buffer;*/
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
