#include "FileStream.h"
#include "../Utilities/MacroUtility/CustomMacros.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "../Utilities/CustomUtility.h"

char* FileStream::ReadAllText(const char* filePath)
{
    // Alocate per 500 bytes. 
    // With each 501th character allocate another 500.
    // After reading is done, resize the pointer to string's length

    size_t allocSize = 500;
    char* buffer = static_cast<char*>(allocate_heap_clean(allocSize, 1));
    size_t buffIdx = 0;

    FILE* file; 
    int opened = fopen_s(&file, filePath, "r");

    if (opened != 0)
        return nullptr;

    while (!feof(file))
    {
        if (allocSize - 1 == buffIdx)
        {
            allocSize += 500;

            buffer = (char*)reallocate_heap_block(buffer, allocSize, 1);
        }

        char* pomBuffer = static_cast<char*>(allocate_heap_clean(1, 1));
        size_t read = fread(pomBuffer, 1, 1, file);

        if (read != 0)
        {
            buffer[buffIdx] = pomBuffer[0];

            buffIdx += 1;
        }

        free(pomBuffer);
    }

    if (buffer[buffIdx] != '\0') // If the last character read from a file isn't null terminator
    {
        if (buffIdx + 1 == allocSize)
            buffer = (char*)reallocate_heap_block(buffer, allocSize + 1, 1);

        buffer[buffIdx + 1] = '\0'; // Add null terminator to last index
        buffIdx += 1;
    }

    buffer = (char*)reallocate_heap_block(buffer, buffIdx + 1, 1);

    fclose(file);  // NOLINT(cert-err33-c)
    return buffer;
}

char** FileStream::ReadAllLines(const char* filePath)
{
    // Alocate per 500 bytes for each line. 
    // With each 501th character allocate another 500 to the line.
    // After reading is done, resize the pointer to file line according to string's length
    // Always allocate one line by one. Next line = alloc += 1;

    FILE* file;
    errno_t res = fopen_s(&file, filePath, "r");
    
    if (res == 0)
        return nullptr;

    check(file);

    int fileIdx   = 0;
    int fileLine  = 0;
    int lineAlloc = 500;

    char** buffer = (char**)allocate_heap_clean(1, sizeof(char*));
    buffer[0] = (char*)allocate_heap_clean(500, 1);

    for (int idx = 0; !feof(file); idx++, fileIdx++)
    {
        //char* pomBuffer = (char*)allocate_heap_clean(1, 1);

        char* buffCharacter = (char*)allocate_heap_clean(2, 1);
        size_t read = fread(buffCharacter, 1, 1, file);

        if (read != 0)
        {
            if (lineAlloc - 1 == fileIdx)
            {
                buffer[fileLine] = buffCharacter[0] == '\n' ?
                    (char*)reallocate_heap_block(buffer[fileLine], lineAlloc += 1, 1) :
                    (char*)reallocate_heap_block(buffer[fileLine], lineAlloc += 500, 1);
            }

            if (buffCharacter[0] == '\n')
            {
                buffer[fileLine][fileIdx] = '\0';

                // Reallocate - Let buffer has allocated only space it needs for storge
                buffer[fileLine] = (char*)reallocate_heap_block(buffer[fileLine], fileIdx + 1, 1);
                fileLine += 1;
                fileIdx = -1; // Increased at the end of the loop to 0

                // fileLine starts at index 0. 0th index = reading 1st line
                // 2nd line in file = fileLine = 1 + 1
                buffer = (char**)reallocate_heap_block(buffer, fileLine + 1, sizeof(char*));  // NOLINT(bugprone-multi-level-implicit-pointer-conversion)
                buffer[fileLine] = (char*)allocate_heap_clean(500, 1);
            }
            else
            {
                buffer[fileLine][fileIdx] = buffCharacter[0];
            }
        }
    }
    // Reallocate last line
    buffer[fileLine] = (char*)reallocate_heap_block(buffer[fileLine], fileIdx + 1, 1);

    size_t closed = fclose(file);

    if (closed == 0)
    {
        std::ostringstream oss{};
        oss << "Couldn't close file " << filePath;
        throw std::runtime_error(oss.str());
    }
    
    return buffer;
}


void FileStream::WriteAllText(const char* filePath, const char* text)
{
    FILE* fPtr;
    size_t opened = fopen_s(&fPtr, filePath, "w");

    if (opened != 0 || fPtr == nullptr)
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Opening file " << filePath << "failed!";

        throw std::runtime_error(oss.str());
    }

    size_t wrote = fwrite(text, 1, strlen(text), fPtr);

    if (wrote != strlen(text))
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Writing text to file " << filePath << "failed!";

        throw std::runtime_error(oss.str());
    }
    
    int closed = fclose(fPtr);
    if (closed == EOF)
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Closing file " << filePath << "failed!";

        throw std::runtime_error(oss.str());
    }
}

void FileStream::WriteAllLines(const char* filePath, const char** content, size_t n_lines)
{
    FILE* file;
    size_t opened = fopen_s(&file, filePath, "w");

    if (opened != 0)
        return;

    size_t allocSize    = 500;
    size_t currentIndex = 0;

    char* stringBuilder = (char*)allocate_heap_clean(allocSize, 1);

    for (size_t line = 0; line < n_lines; line++)
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

    size_t wrote = fwrite(stringBuilder, 1, currentIndex + 1, file);
    if (wrote != currentIndex + 1)
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Writing text to file " << filePath << "failed!";

        throw std::runtime_error(oss.str());
    }

    int closed = fclose(file);
    if (closed == EOF)
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Closing file " << filePath << "failed!";

        throw std::runtime_error(oss.str());
    }
    
    free(stringBuilder);
}

FileStream::FileStream(char*& filePath)
{
    this->filePath = (char*)allocate_heap_clean(strlen(filePath), 1);
    strcpy_c(this->filePath, filePath);
}

FileStream::FileStream(std::string filePath)
{
    this->filePath = (char*)allocate_heap_clean(strlen(filePath.c_str()), 1);
    const char* cStr = filePath.c_str();
    strcpy_c(this->filePath, cStr);
}

FileStream::~FileStream()
{
    if(this->fileStatus == FileStatus::Opened)
    {
        int closed = fclose(this->filePtr);
        if (closed == EOF)
        {
            std::ostringstream oss{};
            oss << __FUNCTION__ << ": Closing file " << this->filePath << "failed!";

            throw std::runtime_error(oss.str());
        }
    }

    free(filePath);
}

bool FileStream::OpenFile(FileOpenMode openMode)
{
    std::vector<const char*> _vec = { "r", "w", "a", "r+", "w+", "a+" };
    const char* mode = _vec[static_cast<int>(openMode)];
    
    if (fileStatus == FileStatus::Closed)
    {
        bool opened = fopen_s(&this->filePtr, this->filePath, mode) == 0 && this->filePtr != nullptr;

        fileStatus = opened ? FileStatus::Opened : FileStatus::Closed;
        return opened;
    }

    return false;
}

bool FileStream::CloseFile()
{
    if (fileStatus == FileStatus::Closed || this->filePtr == nullptr)
    {
        fileStatus = FileStatus::Closed;
        return false;
    }

    int closed = fclose(this->filePtr);
    if (closed == EOF)
    {
        std::ostringstream oss{};
        oss << __FUNCTION__ << ": Closing file " << this->filePath << "failed!";

        throw std::runtime_error(oss.str());
    }
    // Unbind ptr to an opened file
    this->filePtr = nullptr;

    fileStatus = FileStatus::Closed;
    return true;
}
