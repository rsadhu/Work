#include<iostream>
#include"MyThreads.h"
#include"MyCustomThreads.h"
#include"Cpp11Features.h"
#include<vector>
#include<stdio.h>
#include<chrono>
#include<condition_variable>


std::mutex mut,mut1;
std::condition_variable cv;
bool flag = false;

std::thread t1;// (MyThread);
std::thread t2;// (GoThread);

void MyThread()
{
	std::unique_lock<std::mutex> lock(mut);
	while (!flag)
	cv.wait(lock);
	std::cout << " ok i am free to work now \n";	
}

void GoThread()
{
	std::unique_lock<std::mutex> lock(mut);
	for (int i = 0; i < 100; i++)
	std::cout << " Go ThreaD:: working ..." << i << std::endl;
	flag = true;
	cv.notify_one();
}





void func1()
{
	for (int i = 0; i < 10; i++)
	{
		std::lock(mut, mut1);
		std::lock_guard<std::mutex> lock1(mut1, std::adopt_lock);
		std::lock_guard<std::mutex> lock(mut, std::adopt_lock);
		std::cout << "hello ! calling from worker:: thread :: " << std::this_thread::get_id() << std::endl;
	}
}
#include<stack>
#include<deque>

std::deque<int> g_stack;
std::condition_variable cond;


void producerThread()
{
	for (int i = 1; i <= 100; i++)
	{
		std::unique_lock<std::mutex> locker(mut);
		g_stack.push_back(i);
		locker.unlock();
		cond.notify_one();
	}
}

void consumerThread()
{
	int data = -1;
	while (data!=1)
	{
		std::unique_lock<std::mutex> locker(mut);
		cond.wait(locker, [](){ return !g_stack.empty(); });
		
		data = g_stack.back();
		g_stack.pop_back();
		std::cout << " dayta is :: << " << data << std::endl;
		locker.unlock();		
	}
}

bool gl_flag = false;
int gl_var = 0;
std::mutex mu;


void readerThread()
{
	while (gl_var < 100)
	{
		std::unique_lock<std::mutex> locker(mu);
		//cond.wait(locker, [](bool){ return gl_flag;});
		std::cout << " Value now is " << gl_var << std::endl;
		//gl_flag = false;
		locker.unlock();
	}
}

void writerrThread()
{
	
	for (int i = 0; i < 100; i++)
	{
		if (i % 10 == 0)
		{
	//		cond.notify_one();
			//std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		else
		{
			std::unique_lock<std::mutex>locker(mu);
			gl_var++;			
			locker.unlock();
		}
	}
	
}

int main(int argc, char *argv[])
{

	return 0;
}

