
#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{
	class SieveGPU
	{
	public:
		/* Get list of all prime numbers between 1 and n with OpenCL on the GPU. */
		static std::vector<size_t> Sieve(size_t n);
	};

}