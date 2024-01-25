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

int main()
{
    List<int> xd;

    xd.Add(10);
    xd.Add(35);

    for (int i = 0; i < xd.GetCount(); i++)
    {
        cout << "xd[" << i << "] = " << xd[i] << endl;
    }
}