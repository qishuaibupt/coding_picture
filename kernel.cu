#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "math.h"
#include <stdio.h>

__global__ void computeOut(unsigned char *g_indata, unsigned char *g_odata, int imgw, int imgh, int outw, int outh, int viewnum, float LineNum, float InclinationAngle, float MoveValue, bool ifReverse)
{
	int y = blockDim.y * blockIdx.y + threadIdx.y;//�����߳�ID
	int x = blockDim.x * blockIdx.x + threadIdx.x;
	

	if (y<outh && x<outw)
	{
		int i = 0;//��Ӧ�Ӳ�ͼ���

		float step_value = 1.0 / viewnum * LineNum;
		for (int k = 0; k < 3; k++)
		{
			float value_pixel = x * 3 + 3 * y * InclinationAngle + 2 - k;//bgr->rgb��
			//float value_pixel = x * 3 + 3 * y * InclinationAngle ;//bgr->rgb��
			float judge_value = value_pixel - int(value_pixel / LineNum) * LineNum;
			if (0 > judge_value)
			{
				judge_value = judge_value + LineNum;
			}
			int view_point_number = floor(judge_value / step_value);//��0��ʼ �����Ӧ��vied_point


			if (MoveValue < 0)//λ��
				MoveValue = viewnum - abs(MoveValue);
			view_point_number = (view_point_number + (int)MoveValue) % viewnum;


			if (ifReverse)//default true ͨ��vied_point�����Ӳ�ͼ���
			{
				i = viewnum - view_point_number - 1;//��ת
			}
			else
			{
				i = view_point_number;
			}
			unsigned char* temp = g_indata;
			temp = temp + i*imgw *imgh * 3;//��ͼ�񲢲������Դ洢


			if (imgw == outw&& imgh == outh)//��out��ĳһ���ص�����Ӧ���ӵ�
			{//����ߴ���ͬ
				g_odata[y*outw * 4 + 4 * x + k] = temp[y*imgw * 3 + 3 * x + 2 - k]; 
			}
			else{//����ߴ粻��ͬ	
				float orgx = x * imgw / outw;
				float orgy = y * imgh / outh;
				float u = ceil(orgx) - orgx;
				float v = ceil(orgy) - orgy;
				int orgx_i = ceil(orgx);
				int orgy_i = ceil(orgy);
				//˫���Բ�ֵ  
				int tempL = temp[orgy_i * imgw * 3 + 3 * orgx_i + k] * u * v +
					temp[(orgy_i + 1) * imgw * 3 + 3 * orgx_i + k] * (1 - v) * u +
					temp[orgy_i * imgw * 3 + 3 * (orgx_i + 1) + k] * v* (1 - u) +
					temp[(orgy_i + 1) * imgw * 3 + 3 * (orgx_i + 1) + k] * (1 - v) * (1 - u);
				g_odata[y*outw * 4 + 4 * x + 2 - k] = tempL;
				//g_odata[y*outw * 4 + 4 * x + k] = tempL;
			}	
		}//RGB��������
	}//ID��������
}

extern "C"
{
	void launch_cudaProcess_code(unsigned char* g_inframe, unsigned char* g_odata, int in_w, int in_h, int out_w, int out_h, int viewnum, bool ifReverse, int LineNum, float InclinationAngle, int MoveValue)
	{
		cudaError_t error = cudaSuccess;

		dim3 thread = dim3(16, 16);   // block dimensions are fixed to be 256 threads
		dim3 block = dim3((out_w + thread.x - 1) / thread.x, (out_h + thread.y - 1) / thread.y);

		cudaDeviceSynchronize(); //�����豸�ȴ�
		computeOut << <block, thread >> >(g_inframe, g_odata, in_w, in_h, out_w, out_h, viewnum, LineNum, InclinationAngle, MoveValue, ifReverse);

		error = cudaGetLastError();
		if (error != cudaSuccess)
		{
			printf("launch_cudaProcess() failed to launch error = %d\n", error);
		}
	}
}

