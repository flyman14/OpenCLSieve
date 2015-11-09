// SieveOfEratosthenes.cpp : Defines the exported functions for the DLL application.
//

#include "SieveOfEratosthenes.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

#include <algorithm>

//#include <vector>

using namespace std;

namespace SieveOfEratosthenes
{
	vector<size_t> SieveOfEratosthenes::Sieve(size_t n)
	{
		if (n <= 1)
		{
			throw new exception();
		}
		
		//Let A be an array of bool indexed by size_t 2 to n. A[0] = A[1] = false
		bool *A = new bool[n];
		A[0] = false;
		A[1] = false;
		for (size_t i = 2; i < n; i++)
		{
			A[i] = true;
		}
		
		
		//for i = 2 not exceeding sqrt(n)
		for (size_t i = 2; i <= sqrt(n); i++)
		{
			if (A[i]==true)
			{
				for (size_t j = i*i; j <= n; j += i)
				{
					A[j] = false;
				}
			}
		}

		//Write out the list of primes
		//size_t size = 0;
		vector<size_t> sieve;
		for (size_t t = 0; t < n; t++)
		{
			if (A[t]==true)
			{
				//sieve.resize(++size);
				sieve.push_back(t);
			}
		}

		return sieve;
	}

	/// Generate primes using the segmented sieve of Eratosthenes.
	/// This algorithm uses O(n log log n) operations and O(sqrt(n)) space.
	/// @param limit         Sieve primes <= limit.
	/// @param segment_size  Size of the sieve array in bytes.
	///
	void SieveOfEratosthenes::segmented_sieve(int64_t limit)
	{
		int sqrt = (int)std::sqrt((double)limit);
		int segment_size = sqrt;
		int64_t count = (limit < 2) ? 0 : 1;
		int64_t s = 2;
		int64_t n = 3;

		// vector used for sieving
		std::vector<char> sieve(segment_size);

		// generate small primes <= sqrt
		std::vector<char> is_prime(sqrt + 1, 1);
		for (int i = 2; i * i <= sqrt; i++)
		if (is_prime[i])
		for (int j = i * i; j <= sqrt; j += i)
			is_prime[j] = 0;

		std::vector<int> primes;
		std::vector<int> next;

		for (int64_t low = 0; low <= limit; low += segment_size)
		{
			std::fill(sieve.begin(), sieve.end(), 1);

			// current segment = interval [low, high]
			int64_t high = std::min(low + segment_size - 1, limit);

			// store small primes needed to cross off multiples
			for (; s * s <= high; s++)
			{
				if (is_prime[s])
				{
					primes.push_back((int)s);
					next.push_back((int)(s * s - low));
				}
			}
			// sieve the current segment
			for (std::size_t i = 1; i < primes.size(); i++)
			{
				int j = next[i];
				for (int k = primes[i] * 2; j < segment_size; j += k)
					sieve[j] = 0;
				next[i] = j - segment_size;
			}

			for (; n <= high; n += 2)
			if (sieve[n - low]) {// n is a prime
				count++;
				//std::cout << "" << n << std::endl;
			}
		}

		std::cout << count << " primes found." << std::endl;
	}
}
