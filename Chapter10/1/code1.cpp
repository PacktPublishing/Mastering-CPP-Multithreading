#include <cstdio>
#include <ctime>
#include "CL\opencl.h"

#define NUM_ENTRIES 1024

int main() { // (int argc, const char * argv[]) {
    const char* KernelSource = "fft1D_1024_kernel_src.cl"; 
	const cl_uint num = 1;
    clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, 0, 0, (cl_uint*) num); 
    cl_device_id devices[1];
    clGetDeviceIDs(0, CL_DEVICE_TYPE_GPU, num, devices, 0);
	cl_context context = clCreateContextFromType(0, CL_DEVICE_TYPE_GPU, 0, 0, 0);
	clGetDeviceIDs(0, CL_DEVICE_TYPE_DEFAULT, 1, devices, 0);
    cl_command_queue queue = clCreateCommandQueue(context, devices[0], 0, 0);
	cl_mem memobjs[] = { clCreateBuffer(context, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(float) * 2 * NUM_ENTRIES, 0, 0),              
    clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(float) * 2 * NUM_ENTRIES, 0, 0) };
	cl_program program = clCreateProgramWithSource(context, 1, (const char **)& KernelSource, 0, 0);
	clBuildProgram(program, 0, 0, 0, 0, 0);
	cl_kernel kernel = clCreateKernel(program, "fft1D_1024", 0);
	size_t local_work_size[1] = { 256 };
    clSetKernelArg(kernel, 0, sizeof(cl_mem), (void *) &memobjs[0]);
    clSetKernelArg(kernel, 1, sizeof(cl_mem), (void *) &memobjs[1]);
    clSetKernelArg(kernel, 2, sizeof(float) * (local_work_size[0] + 1) * 16, 0);
    clSetKernelArg(kernel, 3, sizeof(float) * (local_work_size[0] + 1) * 16, 0);
	size_t global_work_size[1] = { 256 };
    global_work_size[0] = NUM_ENTRIES;
    local_work_size[0]  =  64;  // Nvidia: 192 or 256
    clEnqueueNDRangeKernel(queue, kernel, 1, 0, global_work_size, local_work_size, 0, 0, 0);
	cl_mem C = clCreateBuffer(context, CL_MEM_WRITE_ONLY, (size), 0, &ret);
    cl_int ret = clEnqueueReadBuffer(queue, memobjs[1], CL_TRUE, 0, sizeof(float) * 2 * NUM_ENTRIES, C, 0, 0, 0);
	clReleaseMemObject(memobjs[0]);
    clReleaseMemObject(memobjs[1]); 
    clReleaseCommandQueue(queue); 
    clReleaseKernel(kernel); 
    clReleaseProgram(program); 
    clReleaseContext(context); 
    free(C);
} 