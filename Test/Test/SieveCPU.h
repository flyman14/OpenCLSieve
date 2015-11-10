
#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{


	class SieveCPU
	{
	public:
		/* Get number of all prime numbers between 1 and n with OpenCL on the CPU. */
		static int Sieve(size_t n);
	};

}