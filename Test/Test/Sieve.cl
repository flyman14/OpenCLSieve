
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

	char A[1000000];
	A[0] = '0';
	A[1] = '1';  

	for(int i=2; i<limit; i++)
	{
		A[i] = true;
	}

	for(int i=2; i<=1000; i++)
	{
		if (A[i]=='1')
		{
			count++;
			for(int j=i*i; j<=limit; j = j+i)
			{
				A[J] = '0';
			}
		}
	}



    result[gid] = count;
}
