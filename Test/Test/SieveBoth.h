
#include <stdlib.h>
#include <vector>

namespace SieveOfEratosthenes
{
	class SieveBoth
	{
	public:
		/* Get list of all prime numbers between 1 and n using OpenCL with the GPU and CPU. */
		static std::vector<size_t> Sieve(size_t n);
	};

}