#pragma once
class FileStream
{
public:
	static char* ReadAllText(const char* filePath);
	static char** ReadAllLines(const char* filePath);

	static void WriteAllText(const char* filePath, const char* text);
	static void WriteAllLines(const char* filePath, const char** content, size_t n_lines);
};