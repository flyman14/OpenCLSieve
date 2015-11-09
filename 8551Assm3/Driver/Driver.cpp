// Driver.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SieveOfEratosthenes.h"
#include "SieveCPU.h"
#include "SieveGPU.h"
#include "SieveBoth.h"
#include <iostream>

#define LIMIT 10000

int _tmain(int argc, _TCHAR* argv[])
{
	int n = LIMIT;

	std::list<int> sieved;

	SieveOfEratosthenes::SieveOfEratosthenes::Sieve(n);

	return 0;
}

