#pragma once
#include <cstdio>
#include <cstring>
#include "../Utilities/MacroUtility/CustomMacros.h"

enum FileStatus : int
{
	Closed = 0,
	Opened = 1
};

class FileStream
{
private:
	char* filePath = nullptr;
	FILE* filePtr  = nullptr;
	FileStatus fileStatus = FileStatus::Closed;

public:

	static char* ReadAllText(const char* filePath);
	static char** ReadAllLines(const char* filePath);

	static void WriteAllText(const char* filePath, const char* text);
	static void WriteAllLines(const char* filePath, const char** content, size_t n_lines);

	FileStream(char*& filePath)
	{
		this->filePath = (char*)allocate_heap_clean(strlen(filePath), 1);
		strcpy_s(this->filePath, strlen(filePath), filePath);
	}

	bool OpenFile(const char* openMode);
	bool CloseFile();
};