#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int a = 0;
mutex mtx;

void thread_function_a(int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		mtx.lock();
		a += 1;
		printf("[A] printf: %d\n", a);
		mtx.unlock();
	}
}

void thread_function_b(int cnt)
{
	for (int i = 0; i < cnt; i++)
	{
		mtx.lock();
		a += 1;
		printf("[B] printf: %d\n", a);
		mtx.unlock();
	}
}

int main(int argc, char* argv[])
{
	// thread
	thread _t_a(thread_function_a, 100);
	thread _t_b(thread_function_b, 100);

	// wait until two threads ends
	_t_a.join();
	_t_b.join();

	return 0;
}