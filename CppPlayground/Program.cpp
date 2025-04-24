#include <iostream>
#include "AsyncTesting/AsyncTest.h"
#include "ColorFolder/Color.h"
#include "File Operations/FileStream.h"
#include "Utilities/CustomUtility.h"
#include "Utilities/ArrayUtility/ArrayFunc.h"
#include "Utilities/ConversionsUtility/Conversions.h"
#include "Utilities/Dynamic String Lib/DynamicStringLibrary.h"
#include "Utilities/MacroUtility/CustomMacros.h"
#include "Utilities/List Utility/List.h"
#include "Utilities/CustomUtility.h"
#include "Utilities/CustomMemoryAllocation/IMemory.h"

using namespace std;

void TestDynamicStringAllocation()
{
    char* myarr = DynamicStringLibrary::CreateDynamicString("ahojky jak se mas?", 19);
    char xd[11] = { 'c', 'a', 'u', 'k', 'y', ' ', 's', 'u', ' ', 'o', 'k' };
    char* myarr2 = DynamicStringLibrary::CreateDynamicString(xd, 11);

    cout << "myarr = " << myarr << '\n';

    char* toExtract = DynamicStringLibrary::CreateDynamicString("afgabcde", 9);
    DynamicStringLibrary::ExtractFirstDynamicString(toExtract, "ab", 2);
    cout << "toExtract: " << toExtract << '\n';


    char* copied = DynamicStringLibrary::CopyDynamicString(toExtract);
    cout << "copied: " << copied << '\n';

    const char* compared = DynamicStringLibrary::CompareDynamicString("abce", "abcde") ? "true" : "false";
    cout << "Compared: " << compared << '\n';

    char arr[6] = { 'a', 'b', 'c', 'd', 'e' };
    
    char* reverse = DynamicStringLibrary::ReverseDynamicString(arr);
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


void NewMemoryCallbackHandle()
{
    cout << "New memory block allocated" << endl;
}

void MemoryEditedHandle()
{
    cout << "Memory block edited" << endl;
}

void MemoryFreedHandle()
{
    cout << "Memory freed!" << endl;
}

void TestIMemory()
{
    IMemory<string> mem = IMemory<string>(10, &NewMemoryCallbackHandle, 
                                              &MemoryEditedHandle, 
                                              &MemoryFreedHandle);

    for (int i = 0; i < mem.GetMemorySize(); i++)
{
        std::ostringstream oss{};
        oss << "mem[" << i << "]";
        mem[i] = oss.str();
    }

    cout << "mem[5] before change: " << mem[5] << endl;

    mem[5] = "mem[455]";

    cout << "mem[5] after change: " << mem[5] << endl;

}

void TestListFunctionality()
{
    int arr[10] = { 0, 0, 0, 3, 4, 5, 5, 5, 8, 9 };

    List<int> myList = List<int>::Copy(arr, 10);

    List<int> copy = myList;
    
    myList.Add(50);
    myList.Remove(5);
    
    int len = static_cast<int>(myList.GetCount());

    List<int> copyWithZero(myList);
    
    myList.Remove(0);
    myList.Remove(0);
    copy.Remove(0);

    int zeroArr[5] = { 0, 0, 0, 0, 0 };

    List<int> allZeroes(zeroArr, 5);
    allZeroes.Remove(0);
    allZeroes.Remove(740);
}

void TestListFunctionalityTwo()
{
    string arr[10] = { "prvni", "druhy", "treti", "ctvrty", "paty", "sesty", "sedmy", "prvni", "prvni", "devet" };

    List<string> myList = List<string>::Copy(arr, 10);

    List<string> copy = myList;
    
    myList.Add("prvni");
    myList.Remove("devet");
    
    int len = static_cast<int>(myList.GetCount());

    List<string> copyWithZero(myList);
    
    myList.Remove("cau");
    myList.Remove("prvni");
    copy.Remove("treti");

    List<string> empty;
    List<string> copyOfEmpty(empty);
}

int main()
{
    
    return 0;
}