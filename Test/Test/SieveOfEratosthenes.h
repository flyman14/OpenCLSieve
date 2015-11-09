

#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{
	/* 
	Class which can use the Sieve of Eratosthenes algorithm to return a list
	of all primes between 1 and n serially.
	*/
	class SieveOfEratosthenes
	{
	public:
		/* Get list of all prime numbers between 1 and n serially. */
		static std::vector<size_t> Sieve(size_t n);

	};
}