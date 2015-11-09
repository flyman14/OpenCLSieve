#pragma once
#ifdef SIEVEOFERATOSTHENES_EXPORTS
#define SIEVEOFERATOSTHENES_API _declspec(dllexport)
#else
#define SIEVEOFERATOSTHENES_API _declspec(dllimport)
#endif

#include <stdlib.h>
#include <list>

namespace SieveOfEratosthenes
{
	static class SieveBoth
	{
	public:
		/* Get list of all prime numbers between 1 and n using OpenCL with the GPU and CPU. */
		static SIEVEOFERATOSTHENES_API std::list<int> Sieve(int n);
	};

}