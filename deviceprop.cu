#include <iostream>
#define cout std::cout
#define endl std::endl;
int main(void)
{
	cudaDeviceProp prop;
	int count;
	cudaErrorCheck(cudaGetDeviceCount(&count));
	for(int i=0;i<count;i++)
	{
		cout<<"Printing details about device "<<i<<endl;
		cudaErrorCheck(cudaGetDeviceProp(&prop,i));
		cout<<"Name: "<<prop.name<<endl;
		cout<<"Total Global Memory: "<<prop.totalGlobalMem<<endl;
		cout<<"Registers per block: "<<prop.regsPerBlock<<endl;
		cout<<"Warp Size: "<<prop.warpSize<<endl;
		cout<<"Max Threads Per Block: "<<prop.maxThreadsPerBlock<<endl;
		cout<<"Max Thread Dimension: "<<prop.maxThreadsDim[0]<<", "<<prop.maxThreadsDim[1]<<", "<<prop.maxThreadsDim[2]<<", "<<endl;
		cout<<"Max Grid Size: "<<prop.maxGridSize[0]<<", "<<prop.maxGridSize[1]<<", "<<prop.maxGridSize[2]<<", "<<endl;
		cout<<"Multi Processor Count: "<<prop.multiProcessorCount<<endl;
	}
}