#pragma once
enum FileStatus : uint8_t
{
	Closed = 0,
	Opened = 1
};

class FileStream
{
private:
	char* filePath = nullptr;
	FILE* filePtr = nullptr;
	FileStatus fileStatus = FileStatus::Closed;


public:

	static char* ReadAllText(const char* filePath);
	static char** ReadAllLines(const char* filePath);

	static void WriteAllText(const char* filePath, const char* text);
	static void WriteAllLines(const char* filePath, const char** content, size_t n_lines);

	FileStream(char*& filePath)
	{
		this->filePath = (char*)allocate_heap_clean(strlen(filePath), 1);
		strcpy(this->filePath, filePath);
	}

	bool OpenFile(const char* openMode);
	bool CloseFile();
};