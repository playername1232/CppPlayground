// VlastniStringAlloc.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include "DynamicStringLibrary.h"

using namespace std;

int main()
{
    char* myarr = DynamicStringLibrary::CreateDynamicString("ahojky wassup", 14);
    char xd[5] = { 'c', 'a', 'u', 'k', 'y' };
    char* myarr2 = DynamicStringLibrary::CreateDynamicString(xd, 5);


    cout << "myarr = " << myarr << endl;

    char* res = DynamicStringLibrary::ConcatenateDynamicString(myarr, myarr2, ' ');
    cout << "res = " << res;

    cin;
}