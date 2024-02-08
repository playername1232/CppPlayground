#pragma once
#include <iostream>       // std::cout
#include <functional>     // std::ref
#include <thread>         // std::thread
#include <future>         // std::promise, std::future

class AsyncTest
{
public:
	void Test1();
	void Test2();
	void Test3();
	void Test4();

	void GeneralTest();
};