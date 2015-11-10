

#include <stdlib.h>
#include <vector>

#include <stdint.h>

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
		static int Sieve(size_t n);

		/* Get list of all prime numbers between 1 and n serially. Uses less memory. */
		static void segmented_sieve(int64_t limit);
	};
}