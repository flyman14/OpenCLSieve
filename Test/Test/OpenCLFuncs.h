#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#define CL_USE_DEPRECATED_OPENCL_2_0_APIS

#ifdef __APPLE__
#include <sys/time.h>

#include <OpenCL/cl.h>
#else
#include <CL/cl.h>

#include <Windows.h>

//#define LIMIT 1000000

#endif

class OpenCLFuncs
{
public:
	/* Function to check return value of OpenCL calls and output custom error message to cerr */
	static bool CheckOpenCLError(cl_int errNum, const char *errMsg);
	
	/* Create an OpenCL context on the first available platform using either a GPU or CPU depending on what is available. */
	static cl_context CreateContext();
	
	/* Create an OpenCL program from the kernel source file */
	static cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device);
	
	/* Create memory objects used as the arguments to the kernel. 
	   The kernel takes three arguments: result (output), a (input), and b (input) */
	static cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName);
	
	/*  Create memory objects used as the arguments to the kernel
	    The kernel takes three arguments: result (output), a (input), and b (input) */
	static bool CreateMemObjects(cl_context context, cl_mem memObjects[3],
		float *a, float *b);
	
	/*  Cleanup any created OpenCL resources */
	static void Cleanup(cl_context context, cl_command_queue commandQueue,
		cl_program program, cl_kernel kernel, cl_mem memObjects[3]);


	static const int ARRAY_SIZE = 10;
	
};
