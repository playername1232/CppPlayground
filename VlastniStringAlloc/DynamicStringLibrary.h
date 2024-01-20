#pragma once
#include <malloc.h>

#define InnerFree(ptr) { free(ptr); }

class DynamicStringLibrary
{
public:

    /// <summary>
    /// Creates new Dynamic String
    /// </summary>
    /// <param name="str">Char array new Dynamic String is gonna be created based on</param>
    /// <param name="len">Length of char array</param>
    /// <returns>Dynamically created Memory pointer</returns>
	static char* CreateDynamicString(const char* str, size_t len);

    /// <summary>
    /// Connects two strings
    /// </summary>
    /// <param name="str">String entry</param>
    /// <param name="concate">String to connect</param>
    /// <param name="splitter">Character put between strings to split</param>
    /// <returns>Dynamically created Memory pointer of two joined string</returns>
    static char* ConcatenateDynamicString(const char* str, const char* concate, const char splitter = NULL);

    /// <summary>
    /// Frees Memory Pointer
    /// </summary>
    /// <param name="str">Memory Pointer</param>
    static void DeleteDynamicString(const char* str) { free(const_cast<char*>(str)); }

    /// <summary>
    /// Frees Memory Pointers
    /// </summary>
    /// <param name="arrToFree">Array of Memory Pointers</param>
    /// <param name="numOfElements">Number of Memory Pointers</param>
    static void DeleteDynamicString(const char** arrToFree, size_t numOfElements);

    /// <summary>
    /// Extracts first occurence of given string from source string
    /// </summary>
    /// <param name="str">Original string</param>
    /// <param name="extractStr">String to remove</param>
    /// <param name="sizeExtract">Length of extracted string</param>
    static void ExtractFirstDynamicString(char*& str, const char* extractStr, size_t sizeExtract);

    /// <summary>
    /// Copies string
    /// </summary>
    /// <param name="str">String to copy</param>
    /// <returns>Dynamically created Memory pointer to copied string</returns>
    static char* CopyDynamicString(const char* str);

    /// <summary>
    /// Compares two strings
    /// </summary>
    /// <param name="str1">First string</param>
    /// <param name="str2">Second string</param>
    /// <returns>Returns wether strings are equal</returns>
    static bool CompareDynamicString(const char* str1, const char* str2);


    /// <summary>
    /// Reverses the string
    /// </summary>
    /// <param name="str">String to reverse</param>
    /// <returns>Dynamically created Memory pointer to reveresed string</returns>
    static char* ReverseDynamicString(const char* str);
};