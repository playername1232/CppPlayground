#pragma once
#include "../Utilities/MacroUtility/CustomMacros.h"

enum FileStatus : int
{
	Closed = 0,
	Opened = 1
};

enum FileOpenMode
{
	Read			= 0,
	Write			= 1,
	Append			= 2,
	ReadUpdate		= 3,
	WriteUpdate		= 4,
	AppendUpdate	= 5
	
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

	FileStream(char*& filePath);
	FileStream(std::string filePath);
	~FileStream();

	bool OpenFile(FileOpenMode openMode);
	bool CloseFile();
};