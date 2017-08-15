//
//  main.c
//  Opencltest
//
//  Created by Shikhar  on 20/06/17.
//  Copyright © 2017 Shikhar . All rights reserved.
//

#include <stdio.h>
#include <OpenCL/cl.h>
#include <time.h>
#include <unistd.h>
#define PROGRAM_FILE "selection_optimised.cl"
#define KERNEL_NAME "test"
int N;
cl_device_id create_device()
{
    cl_platform_id platform;
    cl_device_id dev;
    cl_int err;
    err=clGetPlatformIDs(1, &platform, NULL);
    if(err<0)
    {
        printf("Platform error");
        exit(1);
    }
    
    err=clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &dev, NULL);
    if(err<0)
    {
        printf("Device Error");
        exit(1);
    }
    
    return dev;
}
cl_program create_program(cl_device_id device,cl_context context,const char* filename)
{
    cl_program prog;
    
    FILE *handle=fopen(filename,"r");
    if(handle==NULL)
    {
        perror("File couldn't be opened");
        exit(1);
    }
    
    fseek(handle,0,SEEK_END);
    size_t size=ftell(handle);
    rewind(handle);
    
    char *buffer=(char*)malloc(size+1);
    buffer[size]='\0';
    fread(buffer,sizeof(char),size,handle);
    fclose(handle);
    int err;
    prog=clCreateProgramWithSource(context, 1, (const char**)&buffer, &size, &err);
    if(err<0)
    {
        perror("Program creation error");
        exit(1);
    }
    free(buffer);
    
    err=clBuildProgram(prog, 0, NULL, NULL, NULL, NULL); //CHECK THIS
    if(err<0)
    {
        /* Find size of log and print to std output */
        char *program_log;
        size_t log_size;
        clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG,
                              0, NULL, &log_size);
        program_log = (char*) malloc(log_size + 1);
        program_log[log_size] = '\0';
        clGetProgramBuildInfo(prog, device, CL_PROGRAM_BUILD_LOG,
                              log_size + 1, program_log, NULL);
        printf("%s\n", program_log);
        free(program_log);
        exit(1);
    }
    
    return prog;
    
    
}
int main()
{
    
    FILE *inputfile=fopen("f.txt","r");
    FILE *outputfile=fopen("graph.txt","a");
    fscanf(inputfile,"%d",&N);
    int data[N];
    int out[N];
    for(int i=0;i<N;i++)
    fscanf(inputfile,"%d",&data[i]);
    
    fclose(inputfile);
    
    printf("----------------------------------------------------------------------------------\n\n\n\n\n\n");
    
    //////////////////////////////////////SET UP//////////////////////////////
    
    cl_event timing_event;
    cl_ulong start_time,end_time,read_time;
    
    cl_device_id device;
    cl_context context;
    cl_command_queue queue;
    cl_program program;
    cl_kernel kernel;
    cl_int err;
    device = create_device();
    context=clCreateContext(NULL, 1, &device, NULL, NULL, &err);
    if(err<0)
    {
        perror("Context error");
        exit(1);
    }
    program = create_program(device,context,PROGRAM_FILE);
    kernel=clCreateKernel(program,KERNEL_NAME, &err);
    if(err<0)
    {
        perror("Kernel Creation error");
        exit(1);
    }
    
    queue=clCreateCommandQueue(context, device, CL_QUEUE_PROFILING_ENABLE , &err);
    if(err<0)
    {
        perror("Queue Error");
        exit(1);
    }
    //////////////////////////////////PROGRAM/////////////////////////////////
    cl_mem A= clCreateBuffer(context, CL_MEM_READ_ONLY|CL_MEM_COPY_HOST_PTR, sizeof(data), (void*)data, &err);
    if(err<0)
    {
        
        perror("Creating buffer error in data");
        exit(1);
    }
    cl_mem B= clCreateBuffer(context, CL_MEM_READ_WRITE, sizeof(out), NULL, &err);
    if(err<0)
    {
        perror("Creating buffer error");
        exit(1);
    }
    
    size_t dim=1;
    size_t *global_offset=NULL;
    size_t global_size[]={N};
    size_t local_size[]={5};
    
    err=clSetKernelArg(kernel, 0, sizeof(cl_mem), &A);
    if(err<0)
    {
        perror("Error setting arguments ");
        exit(1);
    }

    err=clSetKernelArg(kernel, 1, sizeof(cl_mem), &B);
    if(err<0)
    {
        perror("Error setting arguments ");
        exit(1);
    }

    err=clSetKernelArg(kernel, 2, sizeof(int)*(10), NULL);
    if(err<0)
    {
        perror("Error setting arguments ");
        exit(1);
    }
    
    /*size_t dim=2;
    size_t global_offset[]={3,5};
    size_t global_size[]={6,4};
    size_t local_size[]={3,2};*/
    
   
    
    err=clEnqueueNDRangeKernel(queue, kernel, dim, global_offset, global_size, local_size, 0, NULL, NULL);
    
    if(err<0)
    {
        perror("Error in Kernel Enqueue");
        exit(1);
    }
    
    clEnqueueReadBuffer(queue, B, CL_TRUE, 0, sizeof out, (void*)out, 0, NULL, NULL);
    /*
    clGetEventProfilingInfo(timing_event,CL_PROFILING_COMMAND_START,sizeof(start_time),&start_time,NULL);
    clGetEventProfilingInfo(timing_event,CL_PROFILING_COMMAND_END,sizeof(end_time),&end_time,NULL);
    read_time=end_time-start_time;
    fprintf(outputfile,"%d %lf\n",N,read_time/1000000000.0);

    */
    printf("DONE!!");
    clReleaseKernel(kernel);
    clReleaseProgram(program);
    clReleaseContext(context);
    size_t timeres;
    clGetDeviceInfo(device,CL_DEVICE_PROFILING_TIMER_RESOLUTION,sizeof(timeres),&timeres,NULL);
    printf("%d\n",timeres);
    
    fclose(outputfile);
    
}
