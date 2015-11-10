
#include "SieveBoth.h"
#include "OpenCLFuncs.h"

using namespace std;

namespace SieveOfEratosthenes
{
	int SieveBoth::Sieve(size_t n)
	{
		cl_context context = 0;
		cl_command_queue commandQueue = 0;
		cl_program program = 0;
		cl_device_id device = 0;
		cl_kernel kernel = 0;
		cl_mem memObjects[2] = { 0, 0 };
		cl_int errNum;

		// Create an OpenCL context on first available platform
		context = OpenCLFuncs::CreateContext();
		if (context == NULL)
		{
			std::cerr << "Failed to create OpenCL context." << std::endl;
			system("pause");
			return 1;
		}

		// Create a command-queue on the first device available
		// on the created context
		commandQueue = OpenCLFuncs::CreateCommandQueue(context, &device);
		if (commandQueue == NULL)
		{
			OpenCLFuncs::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 2;
		}

		// Create OpenCL program from HelloWorld.cl kernel source
		program = OpenCLFuncs::CreateProgram(context, device, "Sieve.cl");
		if (program == NULL)
		{
			OpenCLFuncs::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 3;
		}

		// Create OpenCL kernel
		kernel = clCreateKernel(program, "main_kernel", NULL);
		if (kernel == NULL)
		{
			std::cerr << "Failed to create kernel" << std::endl;
			OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 4;
		}

		// Create memory objects that will be used as arguments to
		// kernel.  First create host memory arrays that will be
		// used to store the arguments to the kernel
		int result = 0;
		int limit = n;
		
		if (!OpenCLFuncs::CreateMemObjectsForSieve(context, memObjects, limit))
		{
			OpenCLFuncs::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 5;
		}

		// Set the kernel arguments (result, a, b)
		errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
		errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
		
		if (errNum != CL_SUCCESS)
		{
			std::cerr << "Error setting kernel arguments." << std::endl;
			OpenCLFuncs::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 6;
		}

		size_t globalWorkSize[1] = { 1 };
		size_t localWorkSize[1] = { 1 };

		timer.Start();

		// Queue the kernel up for execution across the array
		errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
			globalWorkSize, localWorkSize,
			0, NULL, NULL);
		if (errNum != CL_SUCCESS)
		{
			std::cerr << "Error queuing kernel for execution." << std::endl;
			OpenCLFuncs::CleanupSieve(context, commandQueue, program, kernel, memObjects);
			system("pause");
			return 7;
		}

		// Read the output buffer back to the Host
		errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE,
			0, OpenCLFuncs::array_size * sizeof(float), result,
			0, NULL, NULL);
		if (errNum != CL_SUCCESS)
		{
			std::cerr << "Error reading result buffer." << std::endl;
			OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
			delete[] b;
			delete[] a;
			delete[] result;
			system("pause");
			return 1;
		}

		timer.End();
		if (timer.Diff(seconds, useconds))
			std::cerr << "Warning: timer returned negative difference!" << std::endl;
		std::cout << "OpenCL ran in " << seconds << "." << useconds << " seconds" << std::endl << std::endl;

		// Output (some of) the result buffer
		for (int i = 0; i < ((OpenCLFuncs::array_size>100) ? 100 : OpenCLFuncs::array_size); i++)
		{
			std::cout << result[i] << " ";
		}
		std::cout << std::endl << std::endl;
		std::cout << "Executed program succesfully." << std::endl;
		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
		delete[] b;
		delete[] a;
		delete[] result;

		system("pause");
		
		return 0;
	}
}
