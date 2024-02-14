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

        char* pomBuffer = (char*)allocate_heap_clean(1, 1);
        fread(pomBuffer, 1, 1, file);

        buffer[buffIdx] = pomBuffer[0];

        buffIdx += 1;

        free(pomBuffer);
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
}

char** FileStream::ReadAllLines(const char* filePath)
{
    // Alocate per 500 bytes for each line. 
    // With each 501th character allocate another 500 to the line.
    // After reading is done, resize the pointer to file line according to string's length
    // Always allocate one line by one. Next line = alloc += 1;

    // Declaration
    char** buffer = nullptr;

    FILE* file;
    fopen_s(&file, filePath, "r");

    if (file == nullptr)
        throw std::exception("");

    int fileIdx   = 0;
    int fileLine  = 0;
    int lineAlloc = 500;

    buffer = (char**)allocate_heap_clean(1, sizeof(char*));
    buffer[0] = (char*)allocate_heap_clean(500, 1);

    for (int idx = 0; !feof(file); idx++, fileIdx++)
    {
        char* pomBuffer = (char*)allocate_heap_clean(1, 1);
        fread(pomBuffer, 1, 1, file);

        if (lineAlloc - 1 == fileIdx)
        {
            buffer[fileLine] = pomBuffer[0] == '\n' ?
                (char*)reallocate_heap_block(buffer[fileLine], lineAlloc += 1, 1) :
                (char*)reallocate_heap_block(buffer[fileLine], lineAlloc += 500, 1);
        }

        if (pomBuffer[0] == '\n')
        {
            buffer[fileLine][fileIdx] = '\0';

            // Reallocate - Let buffer have allocated only space it needs for storge
            buffer[fileLine] = (char*)reallocate_heap_block(buffer[fileLine], fileIdx + 1, 1);
            fileLine += 1;
            fileIdx = -1; // Increased at the end of the loop to 0

            buffer = (char**)reallocate_heap_block(buffer, fileLine + 1, sizeof(char*));
        }
        else
        {
            buffer[fileLine][fileIdx] = pomBuffer[0];
        }

        free(pomBuffer);
    }

    return buffer;
}


void FileStream::WriteAllText(const char* filePath, const char* text)
{

}

/// <summary>
/// Finds character in string
/// </summary>
/// <param name="content">String entry</param>
/// <param name="_char">Character to find</param>
/// <returns>Index of first character occurence OR -1 if character doesn't exist in given string</returns>
int GetIndexOf(char* content, char _c)
{
    for (int i = 0; content[i] != '\0'; i++)
    {
        if (content[i] == _c)
            return i;
    }
    return -1;
}

/// <summary>
/// Replaces character in 
/// </summary>
/// <param name="content">String Entry</param>
/// <param name="_c">Original character</param>
/// <param name="_r">Replacement character</param>
/// <returns></returns>
int CharReplace(char* content, char _c, char _r)
{
    int ret = -1;
    for (int i = 0; content[i] != '\0'; i++)
    {
        if (content[i] == _c)
        {
            ret = 0;
            content[i] = _r;
        }
    }
    return ret;
}

void FileStream::WriteAllLines(const char* filePath, const char** content, size_t n_lines)
{
    size_t buffIdx = 0;

    FILE* file;
    fopen_s(&file, filePath, "w");

    if (file == nullptr)
        return;

    size_t allocSize    = 500;
    size_t currentIndex = 0;

    char* stringBuilder = (char*)allocate_heap_clean(allocSize, 1);

    for (int line = 0; line < n_lines; line++)
    {
        for (int idx = 0; content[line][idx] != '\0'; idx++, currentIndex++)
        {
            if (currentIndex == allocSize)
                stringBuilder = (char*)reallocate_heap_block(stringBuilder, allocSize += 500, 1);

            // Not printing new line
            if (content[line][idx] == '\0' && line != (n_lines - 1))
                stringBuilder[currentIndex] = '\n';
            else
                stringBuilder[currentIndex] = content[line][idx];
        }
    }

    fwrite(stringBuilder, 1, currentIndex + 1, file);

    free(stringBuilder);
}
