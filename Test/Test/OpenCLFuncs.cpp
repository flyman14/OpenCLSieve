#include "OpenCLFuncs.h"



// Function to check return value of OpenCL calls and
// output custom error message to cerr
bool OpenCLFuncs::CheckOpenCLError(cl_int errNum, const char *errMsg)
{
	if (errNum != CL_SUCCESS)
	{
		std::cerr << errMsg << std::endl;
		return false;
	}
	return true;
}


//  Create an OpenCL context on the first available platform using
//   a GPU.
cl_context OpenCLFuncs::CreateContextGPU()
{
	// First, select an OpenCL platform to run on.  For this example, we
	// simply choose the first available platform.  Normally, you would
	// query for all available platforms and select the most appropriate one.
	cl_platform_id firstPlatformId;
	cl_uint numPlatforms;
	cl_int errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
	if (!CheckOpenCLError(errNum, "Failed to find any OpenCL platforms."))
		return NULL;
	if (numPlatforms <= 0)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return NULL;
	}
	std::cout << std::endl << numPlatforms << " platforms in total" << std::endl;


	// Get information about the platform
	char pname[1024];
	size_t retsize;
	errNum = clGetPlatformInfo(firstPlatformId, CL_PLATFORM_NAME,
		sizeof(pname), (void *)pname, &retsize);
	if (!CheckOpenCLError(errNum, "Could not get platform info"))
		return NULL;
	std::cout << std::endl << "Selected platform <" << pname << ">" << std::endl;


	// Next, create an OpenCL context on the platform
	cl_context_properties contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)firstPlatformId,
		0
	};
	cl_context context = NULL;
	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_GPU,
		NULL, NULL, &errNum);
	if (!CheckOpenCLError(errNum, "Failed to create an OpenCL GPU context."))
		return NULL;

	return context;
}

//  Create an OpenCL context on the first available platform using
//   a CPU.
cl_context OpenCLFuncs::CreateContextCPU()
{
	// First, select an OpenCL platform to run on.  For this example, we
	// simply choose the first available platform.  Normally, you would
	// query for all available platforms and select the most appropriate one.
	cl_platform_id firstPlatformId;
	cl_uint numPlatforms;
	cl_int errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
	if (!CheckOpenCLError(errNum, "Failed to find any OpenCL platforms."))
		return NULL;
	if (numPlatforms <= 0)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return NULL;
	}
	std::cout << std::endl << numPlatforms << " platforms in total" << std::endl;


	// Get information about the platform
	char pname[1024];
	size_t retsize;
	errNum = clGetPlatformInfo(firstPlatformId, CL_PLATFORM_NAME,
		sizeof(pname), (void *)pname, &retsize);
	if (!CheckOpenCLError(errNum, "Could not get platform info"))
		return NULL;
	std::cout << std::endl << "Selected platform <" << pname << ">" << std::endl;


	// Next, create an OpenCL context on the platform
	cl_context_properties contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)firstPlatformId,
		0
	};
	cl_context context = NULL;
	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_CPU,
		NULL, NULL, &errNum);
	if (!CheckOpenCLError(errNum, "Failed to create an OpenCL CPU context."))
		return NULL;

	return context;
}

//  Create an OpenCL context on the first available platform using
//  either a GPU or CPU depending on what is available.
cl_context OpenCLFuncs::CreateContext()
{
	// First, select an OpenCL platform to run on.  For this example, we
	// simply choose the first available platform.  Normally, you would
	// query for all available platforms and select the most appropriate one.
	cl_platform_id firstPlatformId;
	cl_uint numPlatforms;
	cl_int errNum = clGetPlatformIDs(1, &firstPlatformId, &numPlatforms);
	if (!CheckOpenCLError(errNum, "Failed to find any OpenCL platforms."))
		return NULL;
	if (numPlatforms <= 0)
	{
		std::cerr << "Failed to find any OpenCL platforms." << std::endl;
		return NULL;
	}
	std::cout << std::endl << numPlatforms << " platforms in total" << std::endl;


	// Get information about the platform
	char pname[1024];
	size_t retsize;
	errNum = clGetPlatformInfo(firstPlatformId, CL_PLATFORM_NAME,
		sizeof(pname), (void *)pname, &retsize);
	if (!CheckOpenCLError(errNum, "Could not get platform info"))
		return NULL;
	std::cout << std::endl << "Selected platform <" << pname << ">" << std::endl;


	// Next, create an OpenCL context on the platform
	cl_context_properties contextProperties[] =
	{
		CL_CONTEXT_PLATFORM,
		(cl_context_properties)firstPlatformId,
		0
	};
	cl_context context = NULL;
	context = clCreateContextFromType(contextProperties, CL_DEVICE_TYPE_ALL,
		NULL, NULL, &errNum);
	if (!CheckOpenCLError(errNum, "Failed to create an OpenCL GPU or CPU context."))
		return NULL;

	return context;
}



//  Create a command queue on the first device available on the context
cl_command_queue OpenCLFuncs::CreateCommandQueue(cl_context context, cl_device_id *device)
{
	// Get number of devices
	cl_int numDevices;
	size_t retSize;
	cl_int errNum = clGetContextInfo(context, CL_CONTEXT_NUM_DEVICES, sizeof(numDevices), (void *)&numDevices, &retSize);
	if (!CheckOpenCLError(errNum, "Could not get context info!"))
		return NULL;
	std::cout << std::endl << "There are " << numDevices << " devices." << std::endl;


	// Get list of devices
	cl_device_id *deviceList;
	deviceList = (cl_device_id *)malloc(numDevices * sizeof(cl_device_id));
	errNum = clGetContextInfo(context, CL_CONTEXT_DEVICES, numDevices * sizeof(cl_device_id), (void *)deviceList, &retSize);
	if (!CheckOpenCLError(errNum, "Could not get device list!"))
	{
		std::cerr << " ERROR code " << errNum;
		switch (errNum) {
		case CL_INVALID_CONTEXT:
			std::cerr << " (CL_INVALID_CONTEXT)";
			break;
		case CL_INVALID_VALUE:
			std::cerr << " (CL_INVALID_VALUE)";
			break;
		case CL_OUT_OF_RESOURCES:
			std::cerr << " (CL_OUT_OF_RESOURCES)";
			break;
		case CL_OUT_OF_HOST_MEMORY:
			std::cerr << " (CL_OUT_OF_HOST_MEMORY)";
			break;
		default:
			break;
		}
		std::cerr << " size = " << numDevices * sizeof(cl_device_id) << ";" << retSize << std::endl;
		return NULL;
	}


	// Get device information for each device
	cl_device_type devType;
	std::cout << std::endl << "Device list:" << std::endl;
	for (int i = 0; i < numDevices; i++)
	{

		std::cout << "   " << deviceList[i] << ": ";

		// device type
		errNum = clGetDeviceInfo(deviceList[i], CL_DEVICE_TYPE, sizeof(cl_device_type), (void *)&devType, &retSize);
		if (!CheckOpenCLError(errNum, "ERROR getting device info!"))
		{
			free(deviceList);
			return NULL;
		}
		std::cout << " type " << devType << ":";
		if (devType & CL_DEVICE_TYPE_CPU)
			std::cout << " CPU";
		if (devType & CL_DEVICE_TYPE_GPU)
			std::cout << " GPU";
		if (devType & CL_DEVICE_TYPE_ACCELERATOR)
			std::cout << " accelerator";
		if (devType & CL_DEVICE_TYPE_DEFAULT)
			std::cout << " default";

		// device name
		char devName[1024];
		errNum = clGetDeviceInfo(deviceList[i], CL_DEVICE_NAME, 1024, (void *)devName, &retSize);
		if (!CheckOpenCLError(errNum, "ERROR getting device name!"))
		{
			free(deviceList);
			return NULL;
		}
		std::cout << " name=<" << devName << ">" << std::endl;

	}
	std::cout << std::endl;


	// In this example, we just choose the first available device.  In a
	// real program, you would likely use all available devices or choose
	// the highest performance device based on OpenCL device queries
	cl_command_queue commandQueue = clCreateCommandQueue(context, deviceList[0], 0, NULL);
	if (commandQueue == NULL)
	{
		free(deviceList);
		std::cerr << "Failed to create commandQueue for device 0";
		return NULL;
	}

	*device = deviceList[0];

	free(deviceList);

	return commandQueue;
}

////  Constants



//  Create an OpenCL program from the kernel source file
cl_program OpenCLFuncs::CreateProgram(cl_context context, cl_device_id device, const char* fileName)
{
	cl_int errNum;
	cl_program program;

	std::ifstream kernelFile(fileName, std::ios::in);
	if (!kernelFile.is_open())
	{
		std::cerr << "Failed to open file for reading: " << fileName << std::endl;
		return NULL;
	}

	std::ostringstream oss;
	oss << kernelFile.rdbuf();

	std::string srcStdStr = oss.str();
	const char *srcStr = srcStdStr.c_str();
	program = clCreateProgramWithSource(context, 1,
		(const char**)&srcStr,
		NULL, NULL);
	if (program == NULL)
	{
		std::cerr << "Failed to create CL program from source." << std::endl;
		return NULL;
	}

	errNum = clBuildProgram(program, 0, NULL, NULL, NULL, NULL);
	if (errNum != CL_SUCCESS)
	{
		// Determine the reason for the error
		char buildLog[16384];
		clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG,
			sizeof(buildLog), buildLog, NULL);

		std::cerr << "Error in kernel: " << std::endl;
		std::cerr << buildLog;
		clReleaseProgram(program);
		return NULL;
	}

	return program;
}

static int array_size;

//  Create memory objects used as the arguments to the kernel
//  The kernel takes three arguments: result (output), a (input), and b (input)
bool OpenCLFuncs::CreateMemObjects(cl_context context, cl_mem memObjects[3],
	float *a, float *b)
{
	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(float)* array_size, a, NULL);
	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(float)* array_size, b, NULL);
	memObjects[2] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(float)* array_size, NULL, NULL);

	if (memObjects[0] == NULL || memObjects[1] == NULL || memObjects[2] == NULL)
	{
		std::cerr << "Error creating memory objects." << std::endl;
		return false;
	}

	return true;
}

bool OpenCLFuncs::CreateMemObjectsForSieve(cl_context context, cl_mem memObjects[2], int limit)
{
	memObjects[0] = clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
		sizeof(int), &limit, NULL);
	memObjects[1] = clCreateBuffer(context, CL_MEM_READ_WRITE,
		sizeof(int), NULL, NULL);

	if (memObjects[0] == NULL || memObjects[1] == NULL)
	{
		std::cerr << "Error creating memory objects." << std::endl;
		return false;
	}

	return true;
}



//  Cleanup any created OpenCL resources
void OpenCLFuncs::Cleanup(cl_context context, cl_command_queue commandQueue,
	cl_program program, cl_kernel kernel, cl_mem memObjects[3])
{
	for (int i = 0; i < 3; i++)
	{
		if (memObjects[i] != 0)
			clReleaseMemObject(memObjects[i]);
	}
	if (commandQueue != 0)
		clReleaseCommandQueue(commandQueue);

	if (kernel != 0)
		clReleaseKernel(kernel);

	if (program != 0)
		clReleaseProgram(program);

	if (context != 0)
		clReleaseContext(context);

}

//  Cleanup any created OpenCL resources
void OpenCLFuncs::CleanupSieve(cl_context context, cl_command_queue commandQueue,
	cl_program program, cl_kernel kernel, cl_mem memObjects[2])
{
	for (int i = 0; i < 2; i++)
	{
		if (memObjects[i] != 0)
			clReleaseMemObject(memObjects[i]);
	}
	if (commandQueue != 0)
		clReleaseCommandQueue(commandQueue);

	if (kernel != 0)
		clReleaseKernel(kernel);

	if (program != 0)
		clReleaseProgram(program);

	if (context != 0)
		clReleaseContext(context);

}
