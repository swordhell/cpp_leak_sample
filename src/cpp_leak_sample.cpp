#include <iostream>
#include <random>
#include <vector>

// clang++ -o main -fsanitize=address -std=c++11 ./main.cpp

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

int main(int agrn, char* argc[])
{
	leak_sample1();
	return 0;
}
