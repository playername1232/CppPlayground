// TODO: Check for multiple declaration of allocate_heap, allocate_heap_clean and reallocate_heap_block

//1 > Program.obj : error LNK2005 : "void * __cdecl allocate_heap(unsigned __int64,unsigned __int64)" (? allocate_heap@@YAPEAX_K0@Z) already defined in DynamicStringLibrary.obj
//1 > Program.obj : error LNK2005 : "void * __cdecl allocate_heap_clean(unsigned __int64,unsigned __int64)" (? allocate_heap_clean@@YAPEAX_K0@Z) already defined in DynamicStringLibrary.obj
//1 > Program.obj : error LNK2005 : "void * __cdecl reallocate_heap_block(void *,unsigned __int64,unsigned __int64)" (? reallocate_heap_block@@YAPEAXPEAX_K1@Z) already defined in DynamicStringLibrary.obj


#include <iostream>
#include <string>
#include "DynamicStringLibrary.h"
#include "List.h"

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

int main()
{
    TestDynamicStringAllocation3();

    return 0;

    cout << "Begin...";

    List<string> xd;

    xd.Add("ahoj");
    cout << "xd[0] = " << xd[0] << endl;
    //xd.Remove("ahoj");
    xd.Add("cau");
    xd.Add("jak je");

    for (int i = 0; i < xd.GetCount(); i++)
    {
        cout << "xd[" << i << "] = " << xd[i] << endl;
    }
}