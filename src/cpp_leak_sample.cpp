#include <iostream>
#include <random>
#include <vector>
#include <string.h>

#include <chrono>
#include <thread>

// clang++ -o main -D_GLIBCXX_DEBUG -fsanitize=address -std=c++11 -O1 -g ./cpp_leak_sample.cpp
// cmake .. -DCMAKE_CXX_COMPILER=clang++
// g++ -o main -std=c++11 -O1 -g main.cpp
void leak_sample1()
{
	std::uniform_int_distribution<unsigned> u(0, 9);
	std::default_random_engine e;
	char* ptr = nullptr;
	for (int i = 0; i < 10; ++i)
	{
		auto n = u(e);
		if (n < 5)
		{
			if (n < 2)
			{
				if (ptr != nullptr)
				{
					delete[]ptr;
				}
			}
			ptr = new char[i];
		}
		else
		{
		}
	}

	if (ptr != nullptr)
	{
		delete[]ptr;
	}
}

void leak_sample2()
{
	std::uniform_int_distribution<unsigned> u(0, 9);
	std::default_random_engine e;
	char* ptr = nullptr;
	std::vector<char*> vec;
	for (int i = 0; i < 10; ++i)
	{
		auto n = u(e);
		if (n < 5)
		{
			ptr = new char[n];
			// 这个地方将会检查出内存越界
			// heap-buffer-overflow
			memset((void *)ptr,0,n+1);
			vec.push_back(ptr);
		}
		else
		{
			ptr = new char[n];
			vec.push_back(ptr);
			delete ptr;
		}
	}
	vec.clear();
}

void test_new_delete()
{
	char *buff = nullptr;
	for (;;)
	{
		buff = new char[1024];
		delete buff;
		std::this_thread::sleep_for(std::chrono::seconds(10));

	}
}

class A
{
public:
	A()=default;
	~A(){
		std::cout << "~A\n";
	}
};

void test_vector_clear()
{
	std::vector<char *> vec;
	std::vector<A> vecA;
	for(int i = 0; i< 2; i++)
	{
		vec.push_back(new char[2]);
		vecA.emplace_back();
	}
	vec.clear();
	vecA.clear();
}

int main(int agrn, char* argc[])
{
	test_vector_clear();
	//leak_sample1();
	//leak_sample2();
	// test_new_delete();
	return 0;
}
