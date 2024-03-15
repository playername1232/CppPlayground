#include <iostream>
#include "AsyncTesting/AsyncTest.h"
#include "File Operations/FileStream.h"
#include "Utilities/ArrayUtility/ArrayFunc.h"
#include "Utilities/ConversionsUtility/Conversions.h"
#include "Utilities/Dynamic String Lib/DynamicStringLibrary.h"
#include "Utilities/MacroUtility/CustomMacros.h"

using namespace std;

void TestDynamicStringAllocation()
{
    char* myarr = DynamicStringLibrary::CreateDynamicString("ahojky jak se mas?", 19);
    char xd[11] = { 'c', 'a', 'u', 'k', 'y', ' ', 's', 'u', ' ', 'o', 'k' };
    char* myarr2 = DynamicStringLibrary::CreateDynamicString(xd, 11);

    cout << "myarr = " << myarr << '\n';

    char* res = DynamicStringLibrary::ConcatenateDynamicString(myarr, myarr2, ' ');
    cout << "res = " << res << '\n';

    char* toExtract = DynamicStringLibrary::CreateDynamicString("afgabcde", 9);
    DynamicStringLibrary::ExtractFirstDynamicString(toExtract, "ab", 2);
    cout << "toExtract: " << toExtract << '\n';


    char* copied = DynamicStringLibrary::CopyDynamicString(toExtract);
    cout << "copied: " << copied << '\n';

    const char* compared = DynamicStringLibrary::CompareDynamicString("abce", "abcde") ? "true" : "false";
    cout << "Compared: " << compared << '\n';

    char* reverse = DynamicStringLibrary::ReverseDynamicString("abcde");
    cout << "Reversed: " << reverse << '\n';
}

void TestDynamicStringAllocation2()
{
    DynamicStringLibrary str = "xdd";

    cout << "current str = " << str << '\n';
    str += " cau";

    cout << "updated str = " << str << '\n';
}

void TestDynamicStringAllocation3()
{
    DynamicStringLibrary str1 = "ahoj";
    DynamicStringLibrary str2 = "ahoj";

    DynamicStringLibrary res = (str1 == str2 ? "true" : "false");

    cout << "are strings \"" << str1 << "\" and \"" << str2 << "\" same? : " << res << '\n';

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

void TestFileWriteAndRead()
{
    char* content = FileStream::ReadAllText("test.txt");

    reverse_str(content);

    int* arr = static_cast<int*>(allocate_heap_clean(4, sizeof(int)));

    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;

    reverse_array<int>(arr, 4, sizeof(int));

    cout << "Pre-sorted array : " << '\n';

    for (int i = 0; i < 4; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << '\n';
    }

    sort_array(arr, 4);

    cout << "Sorted array : " << '\n';

    for (int i = 0; i < 4; i++)
    {
        cout << "arr[" << i << "] = " << arr[i] << '\n';
    }

    const char* myArr[] =
    {
        "Tohle je prvni Radek",
        "Tohle je druhy radek",
        "Tohle je treti radek"
    };

    FileStream::WriteAllLines("testCopy.txt", myArr, 3);

    char** strArr = FileStream::ReadAllLines("test.txt");

    cout << strArr[0] << '\n' << strArr[1] << '\n';
}

int main()
{
    int num = 120;

    char* str = Conversions::DecToBin<int>(num, 32); // size in bytes * 8 bits

    cout << num << " in binary: " << str << '\n';

    //cout << "beauty binary: " << Conversions::BeautyPrintBinary(str, 32) << '\n';

    int numBack = Conversions::BinToDec(str, 32);

    cout << "Binary: " << str << " = " << numBack << " in Dec";
    
    return 0;
}