#include <iostream>
#include <string>
#include "DynamicStringLibrary.h"
#include "FileStream.h"
#include "List.h"
#include "ArrayFunc.h"
#include "AsyncTest.h"

using namespace std;

void TestDynamicStringAllocation()
{
    char* myarr = DynamicStringLibrary::CreateDynamicString("ahojky jak se mas?", 19);
    char xd[11] = { 'c', 'a', 'u', 'k', 'y', ' ', 's', 'u', ' ', 'o', 'k' };
    char* myarr2 = DynamicStringLibrary::CreateDynamicString(xd, 11);

    cout << "myarr = " << myarr << endl;

    char* res = DynamicStringLibrary::ConcatenateDynamicString(myarr, myarr2, ' ');
    cout << "res = " << res << endl;

    char* toExtract = DynamicStringLibrary::CreateDynamicString("afgabcde", 9);
    DynamicStringLibrary::ExtractFirstDynamicString(toExtract, "ab", 2);
    cout << "toExtract: " << toExtract << endl;


    char* copied = DynamicStringLibrary::CopyDynamicString(toExtract);
    cout << "copied: " << copied << endl;

    const char* compared = DynamicStringLibrary::CompareDynamicString("abce", "abcde") ? "true" : "false";
    cout << "Compared: " << compared << endl;

    char* reverse = DynamicStringLibrary::ReverseDynamicString("abcde");
    cout << "Reversed: " << reverse << endl;
    cin;
}

void TestDynamicStringAllocation2()
{
    DynamicStringLibrary str = "xdd";

    cout << "current str = " << str << endl;
    str += " cau";

    cout << "updated str = " << str << endl;
}

void TestDynamicStringAllocation3()
{
    DynamicStringLibrary str1 = "ahoj";
    DynamicStringLibrary str2 = "ahoj";

    DynamicStringLibrary res = (str1 == str2 ? "true" : "false");

    cout << "are strings \"" << str1 << "\" and \"" << str2 << "\" same? : " << res << endl;

    DynamicStringLibrary str3 = "ahoj";
    DynamicStringLibrary str4 = "cau";

    DynamicStringLibrary res2 = (str3 != str4 ? "true" : "false");

    cout << "are strings \"" << str3 << "\" and \"" << str4 << "\" not equal? : " << res2;
}

void SimpleAsynchronousTest()
{
    AsyncTest xd;

    xd.GeneralTest();
}

int main()
{

    char* content = FileStream::ReadAllText("test.txt");
    
    reverse_str(content);

    int* arr = (int*)allocate_heap_clean(4, sizeof(int));

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;

    reverse_array<int>(arr, 4, sizeof(int));

    cout << "Pre-sorted array : "  << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    sort_array(arr, 4);

    cout << "Sorted array : " << endl;

    for (int i = 0; i < 4; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << endl;
    }

    return 0;

    const char* myArr[] =
    {
        "Tohle je prvni Radek",
        "Tohle je druhy radek",
        "Tohle je treti radek"
    };

    FileStream::WriteAllLines("testCopy.txt", myArr, 3);

    char** strArr = FileStream::ReadAllLines("test.txt");

    cout << strArr[0] << endl << strArr[1] << endl;

    return 0;
}