
#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{


	class SieveCPU
	{
	public:
		/* Get list of all prime numbers between 1 and n with OpenCL on the CPU. */
		static std::vector<size_t> Sieve(size_t n);
	};

}