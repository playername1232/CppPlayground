#include "FileStream.h"
#include "../Utilities/MacroUtility/CustomMacros.h"
#include <iostream>
#include <fstream>
#include <sstream>

char* FileStream::ReadAllText(const char* filePath)
{
    // Alocate per 500 bytes. 
    // With each 501th character allocate another 500.
    // After reading is done, resize the pointer to string's length

    size_t allocSize = 500;
    char* buffer = static_cast<char*>(allocate_heap_clean(allocSize, 1));
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

        char* pomBuffer = static_cast<char*>(allocate_heap_clean(1, 1));
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

    fclose(file);
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

    check(file);

    int fileIdx   = 0;
    int fileLine  = 0;
    int lineAlloc = 500;

    buffer = (char**)allocate_heap_clean(1, sizeof(char*));
    buffer[0] = (char*)allocate_heap_clean(500, 1);

    for (int idx = 0; !feof(file); idx++, fileIdx++)
    {
        //char* pomBuffer = (char*)allocate_heap_clean(1, 1);

        char* buffCharacter = (char*)allocate_heap_clean(2, 1);
        fread(buffCharacter, 1, 1, file);

        if (lineAlloc - 1 == fileIdx)
        {
            buffer[fileLine] = buffCharacter[0] == '\n' ?
                (char*)reallocate_heap_block(buffer[fileLine], lineAlloc += 1, 1) :
                (char*)reallocate_heap_block(buffer[fileLine], lineAlloc += 500, 1);
        }

        if (buffCharacter[0] == '\n')
        {
            buffer[fileLine][fileIdx] = '\0';

            // Reallocate - Let buffer have allocated only space it needs for storge
            buffer[fileLine] = (char*)reallocate_heap_block(buffer[fileLine], fileIdx + 1, 1);
            fileLine += 1;
            fileIdx = -1; // Increased at the end of the loop to 0

            // fileLine starts at 0 index. 0th index = reading 1st line
            // 2nd line in file = fileLine = 1 + 1
            buffer = (char**)reallocate_heap_block(buffer, fileLine + 1, sizeof(char*));
            buffer[fileLine] = (char*)allocate_heap_clean(500, 1);
        }
        else
        {
            buffer[fileLine][fileIdx] = buffCharacter[0];
        }
    }
    // Reallocate last line
    buffer[fileLine] = (char*)reallocate_heap_block(buffer[fileLine], fileIdx + 1, 1);

    fclose(file);
    return buffer;
}


void FileStream::WriteAllText(const char* filePath, const char* text)
{
    FILE* fPtr = fopen(filePath, "w");

    if (fPtr == nullptr)
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Opening file " << filePath << "failed!";

        throw std::runtime_error(oss.str());
    }

    fwrite(text, 1, strlen(text), fPtr);
    fclose(fPtr);
}

void FileStream::WriteAllLines(const char* filePath, const char** content, size_t n_lines)
{
    size_t buffIdx = 0;

    FILE* file = fopen(filePath, "w");

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

    fclose(file);
    free(stringBuilder);
}

bool FileStream::OpenFile(const char* openMode)
{
    if (fileStatus == FileStatus::Closed)
    {
        filePtr = fopen(this->filePath, openMode);

        bool opened = filePtr != nullptr;

        fileStatus = opened ? FileStatus::Opened : FileStatus::Closed;
        return opened;
    }

    return false;
}

bool FileStream::CloseFile()
{
    if (fileStatus == FileStatus::Closed || this->filePtr != nullptr)
    {
        fileStatus = FileStatus::Closed;
        return false;
    }

    fclose(this->filePtr);
    // Unbind ptr to an opened file
    this->filePtr = nullptr;

    fileStatus = FileStatus::Closed;
    return true;
}
