
__kernel void main_kernel(__global const int *n,
						__global int *result)
{
	int gid = get_global_id(0);

	int limit = n[gid];
	int count = 0;

	if (limit<=1)
	{
		result[gid] = 0;
	}

	char A[100];
	A[0] = 0;
	A[1] = 1;  

	for(int i=2; i<100; i++)
	{
		A[i] = true;
	}

	for(int t=2; t<=10; t++)
	{
		if (A[t]==1)
		{
			
			for(int j=t*t; j<=100; j = j+t)
			{
				A[j] = 0;
			}
		}
	}

	for(int i=2; i<100; i++)
	{
		if (A[i]==1)
		{
			count++;
		}
	}

    result[gid] = count;
}
