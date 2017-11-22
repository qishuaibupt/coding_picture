#include<opencv.hpp>
#include<qthread.h>
#include<qmutex.h>
#include<string>
#include<iostream>

#include<d3d_class.h>
#include<cuda_class.h>
using namespace cv;
using namespace std;

class playThread :public QThread{
public:
	playThread();
	~playThread();

	d3dClass myd3d;
	cudaClass mycuda;

	bool stopped=true;
	bool pause=false;
	
	int in_width = 0;
	int in_height = 0;
	int out_width;
	int out_height;

	int view_number = 50;

	int  width = 0;
	int  height = 0;
	int  flag = 0;
	//int  fps = 0;//帧率
	//double waittime = 0;

	//线长 倾角 位移 随时改变!
	float LineNum = 0;
	float InclinationAngle = 0;
	float MoveValue = 0;
	bool ifReverse=true;//翻转

	Mat frame;
	//VideoCapture video_cap;
	Mat pic;
	string addr;//地址

	bool InitThread(HWND temp, string file_name,int out_width, int height,int num);
	void begin();
	void run();
	void pauseThread();
	void stop();
	void destroy();
	void GetFrameSize(int& t_width, int& t_height);
};
