#include <iostream>
#include "SieveOfEratosthenes.h"

#define LIMIT 10000

int main()
{
	size_t n = LIMIT;
	std::vector<size_t> sieve = SieveOfEratosthenes::SieveOfEratosthenes::Sieve(n);

	//sieve = SieveOfEratosthenes::SieveOfEratosthenes::Sieve(n);

	for (size_t i = 0; i < sieve.size(); i++)
	{
		std::cout << "" << sieve[i] << std::endl;
	}

	return 0;
}
