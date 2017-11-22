#ifndef CUDACLASS_H
#define CUDACLASS_H
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

class cudaClass
{
public:
	uchar*   cuda_frame;
	uchar*   cudaLinearMemory;

	int cuda_width;
	int cuda_height;

	int in_width;
	int in_height;

	int out_width;
	int out_height;

	int in_size;
	int out_size;

	int view_num;

	Mat frame;

	void build_frame(int in_width, int in_height, int out_width, int out_height,int num);//Init

	void send(Mat frame);

	void runcuda(bool ifReverse, float LineNum, float InclinationAngle, float MoveValue);
	
	void clear_frame();
};


extern "C"
{
	void launch_cudaProcess_code(unsigned char* g_inframe, unsigned char* g_odata, int in_w, int in_h, int out_w, int out_h, int viewnum, bool ifReverse, int LineNum, float InclinationAngle, int MoveValue);
}
#endif 
