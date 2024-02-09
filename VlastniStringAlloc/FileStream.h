#pragma once
class FileStream
{
public:
	static char* ReadAllText(const char* filePath);
	static char** ReadAllLines(char* filePath);

	static void WriteAllText(char* filePath, char* text);
	static void WriteAllLines(char* filePath, char** content);
};