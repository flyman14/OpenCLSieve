//
//#include <iostream>
//#include <stdlib.h>
#include "OpenCLFuncs.h"
#include "SieveOfEratosthenes.h"
//#include <fstream>
//#include <sstream>
//#define CL_USE_DEPRECATED_OPENCL_2_0_APIS
//
//#ifdef __APPLE__
//#include <sys/time.h>
//
//#include <OpenCL/cl.h>
//#else
//#include <CL/cl.h>
//
//#include <Windows.h>
//
#define LIMIT 1000000

/* FILETIME of Jan 1 1970 00:00:00. */
static const unsigned __int64 epoch = ((unsigned __int64)116444736000000000ULL);

/*
* timezone information is stored outside the kernel so tzp isn't used anymore.
*
* Note: this function is not for Win32 high precision timing purpose. See
* elapsed_time().
*/
int
gettimeofday(struct timeval * tp, struct timezone * tzp)
{
	FILETIME    file_time;
	SYSTEMTIME  system_time;
	ULARGE_INTEGER ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp->tv_sec = (long)((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long)(system_time.wMilliseconds * 1000);

	return 0;
}
//
//
//
//#endif
//
//
// Helper class for timing calculations
class CTiming
{
public:
	CTiming() {}
	~CTiming() {}

	void Start() { gettimeofday(&tvBegin, NULL); }
	void End() { gettimeofday(&tvEnd, NULL); }
	bool Diff(int &seconds, int &useconds)
	{
		long int diff = (tvEnd.tv_usec + 1000000 * tvEnd.tv_sec) -
			(tvBegin.tv_usec + 1000000 * tvBegin.tv_sec);
		seconds = diff / 1000000;
		useconds = diff % 1000000;
		return (diff < 0) ? true : false;
	}

private:
	struct timeval tvBegin, tvEnd, tvDiff;

};
//
//
//
//
//// Function to check return value of OpenCL calls and
//// output custom error message to cerr
//bool CheckOpenCLError(cl_int errNum, const char *errMsg)
//{
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << errMsg << std::endl;
//		return false;
//	}
//	return true;
//}
//
//
//
//
////  Create an OpenCL context on the first available platform using
////  either a GPU or CPU depending on what is available.
//cl_context CreateContext()
//{
//	// First, select an OpenCL platform to run on.  For this example, we
//	// simply choose the first available platform.  Normally, you would
//	// query for all available platforms and select the most appropriate one.
//	cl_platform_id firstPlatformId;
//	cl_uint numPlatforms;
//	cl_int errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
//	if (!CheckOpenCLError(errNum, "Failed to find any OpenCL platforms."))
//		return NULL;
//	if (numPlatforms <= 0)
//	{
//		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
//		return NULL;
//	}
//	std::cout << std::endl << numPlatforms << " platforms in total" << std::endl;
//
//
//	// Get information about the platform
//	char pname[1024];
//	size_t retsize;
//	errNum = clGetPlatformInfo(firstPlatformId, CL_PLATFORM_NAME,
//		sizeof(pname), (void *)pname, &retsize);
//	if (!CheckOpenCLError(errNum, "Could not get platform info"))
//		return NULL;
//	std::cout << std::endl << "Selected platform <" << pname << ">" << std::endl;
//
//
//	// Next, create an OpenCL context on the platform
//	cl_context_properties contextProperties[] =
//	{
//		CL_CONTEXT_PLATFORM,
//		(cl_context_properties)firstPlatformId,
//		0
//	};
//	cl_context context = NULL;
//	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_ALL,
//		NULL, NULL, &errNum);
//	if (!CheckOpenCLError(errNum, "Failed to create an OpenCL GPU or CPU context."))
//		return NULL;
//
//	return context;
//}
//
//
//
////  Create a command queue on the first device available on the context
//cl_command_queue CreateCommandQueue(cl_context context, cl_device_id *device)
//{
//	// Get number of devices
//	cl_int numDevices;
//	size_t retSize;
//	cl_int errNum = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(numDevices), (void *)&numDevices, &retSize);
//	if (!CheckOpenCLError(errNum, "Could not get context info!"))
//		return NULL;
//	std::cout << std::endl << "There are " << numDevices << " devices." << std::endl;
//
//
//	// Get list of devices
//	cl_device_id *deviceList;
//	deviceList = (cl_device_id *)malloc(numDevices * sizeof(cl_device_id));
//	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, numDevices * sizeof(cl_device_id), (void *)deviceList, &retSize);
//	if (!CheckOpenCLError(errNum, "Could not get device list!"))
//	{
//		std::cerr << " ERROR code " << errNum;
//		switch (errNum) {
//		case CL_INVALID_CONTEXT:
//			std::cerr << " (CL_INVALID_CONTEXT)";
//			break;
//		case CL_INVALID_VALUE:
//			std::cerr << " (CL_INVALID_VALUE)";
//			break;
//		case CL_OUT_OF_RESOURCES:
//			std::cerr << " (CL_OUT_OF_RESOURCES)";
//			break;
//		case CL_OUT_OF_HOST_MEMORY:
//			std::cerr << " (CL_OUT_OF_HOST_MEMORY)";
//			break;
//		default:
//			break;
//		}
//		std::cerr << " size = " << numDevices * sizeof(cl_device_id) << ";" << retSize << std::endl;
//		return NULL;
//	}
//
//
//	// Get device information for each device
//	cl_device_type devType;
//	std::cout << std::endl << "Device list:" << std::endl;
//	for (int i = 0; i < numDevices; i++)
//	{
//
//		std::cout << "   " << deviceList[i] << ": ";
//
//		// device type
//		errNum = clGetDeviceInfo(deviceList[i], CL_DEVICE_TYPE, sizeof(cl_device_type), (void *)&devType, &retSize);
//		if (!CheckOpenCLError(errNum, "ERROR getting device info!"))
//		{
//			free(deviceList);
//			return NULL;
//		}
//		std::cout << " type " << devType << ":";
//		if (devType & CL_DEVICE_TYPE_CPU)
//			std::cout << " CPU";
//		if (devType & CL_DEVICE_TYPE_GPU)
//			std::cout << " GPU";
//		if (devType & CL_DEVICE_TYPE_ACCELERATOR)
//			std::cout << " accelerator";
//		if (devType & CL_DEVICE_TYPE_DEFAULT)
//			std::cout << " default";
//
//		// device name
//		char devName[1024];
//		errNum = clGetDeviceInfo(deviceList[i], CL_DEVICE_NAME, 1024, (void *)devName, &retSize);
//		if (!CheckOpenCLError(errNum, "ERROR getting device name!"))
//		{
//			free(deviceList);
//			return NULL;
//		}
//		std::cout << " name=<" << devName << ">" << std::endl;
//
//	}
//	std::cout << std::endl;
//
//
//	// In this example, we just choose the first available device.  In a
//	// real program, you would likely use all available devices or choose
//	// the highest performance device based on OpenCL device queries
//	cl_command_queue commandQueue = clCreateCommandQueue(context, deviceList[0], 0, NULL);
//	if (commandQueue == NULL)
//	{
//		free(deviceList);
//		std::cerr << "Failed to create commandQueue for device 0";
//		return NULL;
//	}
//
//	*device = deviceList[0];
//
//	free(deviceList);
//
//	return commandQueue;
//}
//
////  Constants
//const int ARRAY_SIZE = 10;
//int array_size = 0;
//
//
////  Create an OpenCL program from the kernel source file
//cl_program CreateProgram(cl_context context, cl_device_id device, const char* fileName)
//{
//	cl_int errNum;
//	cl_program program;
//
//	std::ifstream kernelFile(fileName, std::ios::in);
//	if (!kernelFile.is_open())
//	{
//		std::cerr << "Failed to open file for reading: " << fileName << std::endl;
//		return NULL;
//	}
//
//	std::ostringstream oss;
//	oss << kernelFile.rdbuf();
//
//	std::string srcStdStr = oss.str();
//	const char *srcStr = srcStdStr.c_str();
//	program = clCreateProgramWithSource(context, 1,
//		(const char**)&srcStr,
//		NULL, NULL);
//	if (program == NULL)
//	{
//		std::cerr << "Failed to create CL program from source." << std::endl;
//		return NULL;
//	}
//
//	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		// Determine the reason for the error
//		char buildLog[16384];
//		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
//			sizeof(buildLog), buildLog, NULL);
//
//		std::cerr << "Error in kernel: " << std::endl;
//		std::cerr << buildLog;
//		clReleaseProgram(program);
//		return NULL;
//	}
//
//	return program;
//}
//
//
//
////  Create memory objects used as the arguments to the kernel
////  The kernel takes three arguments: result (output), a (input), and b (input)
//bool CreateMemObjects(cl_context context, cl_mem memObjects[3],
//	float *a, float *b)
//{
//	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//		sizeof(float)* array_size, a, NULL);
//	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
//		sizeof(float)* array_size, b, NULL);
//	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,
//		sizeof(float)* array_size, NULL, NULL);
//
//	if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL)
//	{
//		std::cerr << "Error creating memory objects." << std::endl;
//		return false;
//	}
//
//	return true;
//}
//
//
//
////  Cleanup any created OpenCL resources
//void Cleanup(cl_context context, cl_command_queue commandQueue,
//	cl_program program, cl_kernel kernel, cl_mem memObjects[3])
//{
//	for (int i = 0; i < 3; i++)
//	{
//		if (memObjects[i] != 0)
//			clReleaseMemObject(memObjects[i]);
//	}
//	if (commandQueue != 0)
//		clReleaseCommandQueue(commandQueue);
//
//	if (kernel != 0)
//		clReleaseKernel(kernel);
//
//	if (program != 0)
//		clReleaseProgram(program);
//
//	if (context != 0)
//		clReleaseContext(context);
//
//}

int main()
{
	size_t n = LIMIT;
	std::vector<size_t> sieve;

	CTiming timer;
	int seconds, useconds;
	timer.Start();
	SieveOfEratosthenes::SieveOfEratosthenes::segmented_sieve(LIMIT);
	SieveOfEratosthenes::SieveOfEratosthenes::segmented_sieve(LIMIT);
	SieveOfEratosthenes::SieveOfEratosthenes::segmented_sieve(LIMIT);
	SieveOfEratosthenes::SieveOfEratosthenes::segmented_sieve(LIMIT);
	SieveOfEratosthenes::SieveOfEratosthenes::segmented_sieve(LIMIT);
	timer.End();
	if (timer.Diff(seconds, useconds))
		std::cerr << "warning: timer returned negative difference!" << std::endl;
	std::cout << "serially ran in " << seconds << "." << useconds << " seconds" << std::endl << std::endl;
	

	//sieve = SieveOfEratosthenes::SieveOfEratosthenes::Sieve(n);

	for (size_t i = 0; i < sieve.size(); i++)
	{
	std::cout << "" << sieve[i] << std::endl;
	}

	system("pause");

	//std::cin >> n;

	return 0;
}

//  Constants
const int ARRAY_SIZE = 10;
int array_size = 0;
//
////	main() for HelloWorld example
//int main(int argc, char** argv)
//{
//	OpenCLFuncs::array_size = OpenCLFuncs::ARRAY_SIZE;
//	if (argc > 1)
//		OpenCLFuncs::array_size = atoi(argv[1]);
//
//	cl_context context = 0;
//	cl_command_queue commandQueue = 0;
//	cl_program program = 0;
//	cl_device_id device = 0;
//	cl_kernel kernel = 0;
//	cl_mem memObjects[3] = { 0, 0, 0 };
//	cl_int errNum;
//
//	// Create an OpenCL context on first available platform
//	context = OpenCLFuncs::CreateContext();
//	if (context == NULL)
//	{
//		std::cerr << "Failed to create OpenCL context." << std::endl;
//		system("pause");
//		return 1;
//	}
//
//	// Create a command-queue on the first device available
//	// on the created context
//	commandQueue = OpenCLFuncs::CreateCommandQueue(context, &device);
//	if (commandQueue == NULL)
//	{
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		system("pause");
//		return 1;
//	}
//
//	// Create OpenCL program from HelloWorld.cl kernel source
//	program = OpenCLFuncs::CreateProgram(context, device, "HelloWorld.cl");
//	if (program == NULL)
//	{
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		system("pause");
//		return 1;
//	}
//
//	// Create OpenCL kernel
//	kernel = clCreateKernel(program, "hello_kernel", NULL);
//	if (kernel == NULL)
//	{
//		std::cerr << "Failed to create kernel" << std::endl;
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		system("pause");
//		return 1;
//	}
//
//	// Create memory objects that will be used as arguments to
//	// kernel.  First create host memory arrays that will be
//	// used to store the arguments to the kernel
//	float *result = new float[OpenCLFuncs::array_size];
//	float *a = new float[OpenCLFuncs::array_size];
//	float *b = new float[OpenCLFuncs::array_size];
//	for (int i = 0; i < OpenCLFuncs::array_size; i++)
//	{
//		a[i] = (float)i;
//		b[i] = (float)(i * 2);
//	}
//
//	CTiming timer;
//	int seconds, useconds;
//	timer.Start();
//	for (int i = 0; i < OpenCLFuncs::array_size; i++)
//	{
//		result[i] = a[i] + b[i];
//	}
//	timer.End();
//	if (timer.Diff(seconds, useconds))
//		std::cerr << "Warning: timer returned negative difference!" << std::endl;
//	std::cout << "Serially ran in " << seconds << "." << useconds << " seconds" << std::endl << std::endl;
//
//	if (!OpenCLFuncs::CreateMemObjects(context, memObjects, a, b))
//	{
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		delete[] b;
//		delete[] a;
//		delete[] result;
//		system("pause");
//		return 1;
//	}
//
//	// Set the kernel arguments (result, a, b)
//	errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
//	errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
//	errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error setting kernel arguments." << std::endl;
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		delete[] b;
//		delete[] a;
//		delete[] result;
//		system("pause");
//		return 1;
//	}
//
//	size_t globalWorkSize[1] = { OpenCLFuncs::array_size };
//	size_t localWorkSize[1] = { 1 };
//
//	timer.Start();
//
//	// Queue the kernel up for execution across the array
//	errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL,
//		globalWorkSize, localWorkSize,
//		0, NULL, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error queuing kernel for execution." << std::endl;
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		delete[] b;
//		delete[] a;
//		delete[] result;
//		system("pause");
//		return 1;
//	}
//
//	// Read the output buffer back to the Host
//	errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE,
//		0, OpenCLFuncs::array_size * sizeof(float), result,
//		0, NULL, NULL);
//	if (errNum != CL_SUCCESS)
//	{
//		std::cerr << "Error reading result buffer." << std::endl;
//		OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//		delete[] b;
//		delete[] a;
//		delete[] result;
//		system("pause");
//		return 1;
//	}
//
//	timer.End();
//	if (timer.Diff(seconds, useconds))
//		std::cerr << "Warning: timer returned negative difference!" << std::endl;
//	std::cout << "OpenCL ran in " << seconds << "." << useconds << " seconds" << std::endl << std::endl;
//
//	// Output (some of) the result buffer
//	for (int i = 0; i < ((OpenCLFuncs::array_size>100) ? 100 : OpenCLFuncs::array_size); i++)
//	{
//		std::cout << result[i] << " ";
//	}
//	std::cout << std::endl << std::endl;
//	std::cout << "Executed program succesfully." << std::endl;
//	OpenCLFuncs::Cleanup(context, commandQueue, program, kernel, memObjects);
//	delete[] b;
//	delete[] a;
//	delete[] result;
//
//	system("pause");
//
//	return 0;
//}



