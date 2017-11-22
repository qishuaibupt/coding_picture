#include<play_thread.h>
playThread::playThread()
{
	stopped = true;
	pause = true;
}


playThread::~playThread()
{
	stopped = true;
	pause = true;
	mycuda.clear_frame();
	myd3d.CleanupDevice();
}


bool playThread::InitThread(HWND label_hwnd, string file_name, int t_out_width, int t_out_height, int num)//拿到句柄 文件路径
{
	addr = file_name;
	//video_cap.open(addr);
	//width = video_cap.get(CV_CAP_PROP_FRAME_WIDTH);
	//height = video_cap.get(CV_CAP_PROP_FRAME_HEIGHT);
	//fps = video_cap.get(CV_CAP_PROP_FPS);
	//waittime = 1000.0 / (double)fps;//算帧率

	pic = imread(addr);//载入图片
	int cuda_width = pic.cols;
	int cuda_height = pic.rows;


	myd3d.InitDevice(label_hwnd, t_out_width, t_out_height);
	myd3d.buildTexture(t_out_width, t_out_height);
	mycuda.build_frame(cuda_width, cuda_height, t_out_width, t_out_height, num);
	return true;
}


void playThread::begin()
{
	stopped = false;
	pause = false;
}


void playThread::run()
{
	while (!stopped)
	{

		if (pause)
			continue;

			//double start = static_cast<double>(getTickCount());//tick_star

			//video_cap >> frame;	
			frame = pic;
			/*if (frame.empty())
				break;*/

			mycuda.send(frame);//图片送入CUDA
			mycuda.runcuda(ifReverse,LineNum, InclinationAngle, MoveValue);
			myd3d.Render(mycuda.cudaLinearMemory);
			//Sleep(100);
			
			//double time = ((double)getTickCount() - start) / getTickFrequency();//tick_end
			//
			//if (waittime > time)
			//	Sleep(waittime - time);
		
		}	
}


void playThread::pauseThread()
{
	pause = true;
}


void playThread::stop()
{
	stopped = true;
}


void playThread::destroy()
{
	stopped = true;
	pause = true;
	myd3d.CleanupDevice();
	mycuda.clear_frame();
}


void playThread::GetFrameSize(int& t_width, int& t_height)
{
	t_width = width;
	t_height = height;
}