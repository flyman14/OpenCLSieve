
#include "SieveBoth.h"

using namespace std;

namespace SieveOfEratosthenes
{
	static vector<size_t> Sieve(size_t n)
	{
		if (n <= 1)
		{
			throw new exception();
		}

		//Let A be an array of bool indexed by size_t 2 to n. A[0] = A[1] = false
		bool *A = new bool[n];
		for (size_t i = 2; i < n; i++)
		{
			A[i] = true;
		}
		A[0] = A[1] = false;

		//for i = 2 not exceeding sqrt(n)
		for (size_t i = 2; i <= sqrt(n); i++)
		{
			if (A[i])
			{
				for (size_t j = i*i; j <= n; j += i)
				{
					A[j] = false;
				}
			}
		}

		//Write out the list of primes
		size_t size = 0;
		vector<size_t> sieve(size);
		for (size_t t = 0; t < n; t++)
		{
			if (A[t])
			{
				sieve.resize(++size);
				sieve.push_back(t);
			}
		}

		return sieve;
	}
}
