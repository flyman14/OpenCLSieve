
#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{
	class SieveGPU
	{
	public:
		/* Get number of all prime numbers between 1 and n with OpenCL on the GPU. */
		static int Sieve(size_t n);
	};

}