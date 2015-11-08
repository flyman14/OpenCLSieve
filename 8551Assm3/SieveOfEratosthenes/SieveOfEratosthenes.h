#ifdef SIEVEOFERATOSTHENES_EXPORTS
#define SIEVEOFERATOSTHENES_API _declspec(dllexport)
#else
#define SIEVEOFERATOSTHENES_API _declspec(dllimport)
#endif

#include <stdlib.h>
#include <list>

namespace SieveOfEratosthenes
{
	/** 
	Class which can use the Sieve of Eratosthenes algorithm to return a list
	of all primes between 1 and n, or can return an array of the first n primes. 
	*/
	static class SieveOfEratosthenes
	{
	public:
		/** Get list of all prime numbers between 1 and n. */
		static SIEVEOFERATOSTHENES_API std::list<int> Sieve(int n);

		/** Get array containing the first n prime numbers. */
		static SIEVEOFERATOSTHENES_API int* GetPrimes(int n);


	};
}