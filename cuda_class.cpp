#include "cuda_class.h"

void cudaClass::build_frame(int t_in_width, int t_in_height, int t_out_width, int t_out_height,int num)
{
	cuda_width = t_in_width;
	cuda_height = t_in_height;
	view_num = num;

	in_width = cuda_width;//视差图尺寸
	in_height = cuda_height / view_num;

	out_width = t_out_width;
	out_height = t_out_height;

	in_size = sizeof(unsigned char)* cuda_width * cuda_height * 3;
	out_size = sizeof(unsigned char)* out_width * out_height * 4;

	cudaMalloc(&cuda_frame, in_size);
	cudaMalloc(&cudaLinearMemory, out_size);
}


void cudaClass::send(Mat video_fream)
{
	cudaMemcpy(cuda_frame, video_fream.data, in_size, cudaMemcpyHostToDevice);
	//设备指针 主机指针 单元数目 传递方向
}


void cudaClass::clear_frame()//释放空间
{
	cudaFree(cuda_frame);
	cudaFree(cudaLinearMemory);
}


void cudaClass::runcuda( bool ifReverse, float LineNum, float InclinationAngle, float MoveValue)
{
	cudaDeviceSynchronize();
	launch_cudaProcess_code(cuda_frame, cudaLinearMemory, in_width, in_height, out_width, out_height, view_num, ifReverse, LineNum, InclinationAngle, MoveValue);
}
