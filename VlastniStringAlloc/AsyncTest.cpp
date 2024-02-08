#include "AsyncTest.h"

using namespace std;
using namespace std::chrono_literals;

void AsyncTest::Test1()
{
	future<void> launch2nd = async(launch::async, &AsyncTest::Test2, this);

	for (int i = 0; i < 500; i++)
	{
		std::cout << "Test1() i = " << i << std::endl;
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	cout << endl << endl << "Test1() finished! Waiting for Test2()" << endl << endl;

	launch2nd.wait();

	cout << endl << endl << "Test1() call: Test2() finished!" << endl << endl;
	
	cout << endl << endl << "Test3() laucnhed!" << endl << endl;

	future<void> launch3rd = async(launch::async, &AsyncTest::Test3, this);

	cout << endl << endl << "Test1() exit reached!" << endl << endl;
}

void AsyncTest::Test2()
{
	for (int i = 0; i < 400; i++)
	{
		std::cout << "Test2() i = " << i << std::endl;
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	cout << endl << endl << "Test2() finished!" << endl << endl;
}

void AsyncTest::Test3()
{
	bool launched = false;
	for (int i = 0; i < 300; i++)
	{
		std::cout << "Test3() i = " << i << std::endl;
		this_thread::sleep_for(chrono::milliseconds(100));

		if (i == 150 && !launched)
		{
			launched = true;
			future<void> launch4th = async(launch::async, &AsyncTest::Test4, this);

			cout << endl << endl << "Test3() launched Test4() waiting for exit" << endl << endl;
			launch4th.wait();
			cout << endl << endl << "Test3() call: Test4() finished! Continuing in Test3()" << endl << endl;
		}
	}

	cout << endl << endl << "Test3() finished!" << endl << endl;
}

void AsyncTest::Test4()
{
	for (int i = 0; i < 200; i++)
	{
		std::cout << "Test4() i = " << i << std::endl;
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	cout << endl << endl << "Test4() finished!" << endl << endl;
}

void AsyncTest::GeneralTest()
{
	future<void> future1 = async(launch::async, &AsyncTest::Test1, this);
	future1.wait();

	cout << endl << endl << "GeneralTest() call: All tests finished!!!" << endl << endl;
}
