#pragma once
class FileStream
{
	char* ReadAllText(char* filePath);
	char** ReadAllLines(char* filePath);

	void WriteAllText(char* filePath, char* text);
	void WriteAllLines(char* filePath, char** content);
};

