#include <iostream>
#include <random>
#include <vld.h>

int main(int agrn, char* argc[]) {
	std::uniform_int_distribution<unsigned> u(0, 9);
	std::default_random_engine e;
	char* ptr = nullptr;
	for (int i=0;i<10;++i)
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
	return 0;
}