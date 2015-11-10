
#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{
	class SieveBoth
	{
	public:
		/* Get number of all prime numbers between 1 and n using OpenCL with the GPU and CPU. */
		static int Sieve(size_t n);
	};

}