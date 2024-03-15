#include "AsyncTest.h"

using namespace std;
using namespace std::chrono_literals;

void AsyncTest::Test1()
{
	future<void> launch2nd = async(launch::async, &AsyncTest::Test2, this);

	for (int i = 0; i < 500; i++)
	{
		std::cout << "Test1() i = " << i << '\n';
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	cout << '\n\n' << "Test1() finished! Waiting for Test2()" << '\n\n';

	launch2nd.wait();

	cout << '\n\n' << "Test1() call: Test2() finished!" << '\n\n';
	
	cout << '\n\n' << "Test3() laucnhed!" << '\n\n';

	future<void> launch3rd = async(launch::async, &AsyncTest::Test3, this);

	cout << '\n\n' << "Test1() exit reached!" << '\n\n';
}

void AsyncTest::Test2()
{
	for (int i = 0; i < 400; i++)
	{
		std::cout << "Test2() i = " << i << '\n';
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	cout << '\n\n' << "Test2() finished!" << '\n\n';
}

void AsyncTest::Test3()
{
	bool launched = false;
	for (int i = 0; i < 300; i++)
	{
		std::cout << "Test3() i = " << i << '\n';
		this_thread::sleep_for(chrono::milliseconds(100));

		if (i == 150 && !launched)
		{
			launched = true;
			future<void> launch4th = async(launch::async, &AsyncTest::Test4, this);

			cout << '\n\n' << "Test3() launched Test4() waiting for exit" << '\n\n';
			launch4th.wait();
			cout << '\n\n' << "Test3() call: Test4() finished! Continuing in Test3()" << '\n\n';
		}
	}

	cout << '\n\n' << "Test3() finished!" << '\n\n';
}

void AsyncTest::Test4()
{
	for (int i = 0; i < 200; i++)
	{
		std::cout << "Test4() i = " << i << '\n';
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	cout << '\n\n' << "Test4() finished!" << '\n\n';
}

void AsyncTest::GeneralTest()
{
	future<void> future1 = async(launch::async, &AsyncTest::Test1, this);
	future1.wait();

	cout << '\n\n' << "GeneralTest() call: All tests finished!!!" << '\n\n';
}
