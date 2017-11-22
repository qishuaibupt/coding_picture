#include "player.h"

player::player(QWidget *parent)
	: QMainWindow(parent)
{
	pause = false;
	ui.setupUi(this);

	ui.label->setText(QString::fromLocal8Bit("播放器 V1.0"));//防止汉字乱码 fromLocal8bit
	ui.label->setFont(QFont("Times", 30));
	ui.label->setFrameShape(QFrame::Box); //边框样式

	QPalette m_nColor;
	ui.label->setAutoFillBackground(true);//important 设置窗体自动填充背景
	m_nColor.setColor(QPalette::Background, Qt::gray);
	ui.label->setPalette(m_nColor);	

	QPalette m_nColor2;
	ui.label_2->setAutoFillBackground(true);
	ui.label_3->setAutoFillBackground(true);
	ui.label_4->setAutoFillBackground(true);
	m_nColor2.setColor(QPalette::Background, Qt::white);
	ui.label_2->setPalette(m_nColor);
	ui.label_3->setPalette(m_nColor);
	ui.label_4->setPalette(m_nColor);

	//float LineNum = 17.0361996;
	//float InclinationAngle = 0;
	//float MoveValue = 0;
	ui.doubleSpinBox->setValue(1);
	ui.doubleSpinBox_2->setValue(0);
	ui.doubleSpinBox_3->setValue(0);
}


player::~player()
{
	//mythread.destroy();
	mythread.stop();//结束进程
	mythread.quit();
	mythread.wait();
}

void player::esc()
{
	
	ui.label->setWindowFlags(Qt::Dialog);
	ui.label->showFullScreen();
}

void player::play_start()
{
	//pause = !pause;
	//if (pause)//play
	//{
		mythread.begin();
		mythread.start();
		//ui.play->setText(QString::fromLocal8Bit("暂停"));
	//}
	//else{//pause
		//mythread.pauseThread(); 
		//ui.play->setText(QString::fromLocal8Bit("播放"));
	//}
}


void player::load_video()
{
	QFileDialog chooseData;

	chooseData.setWindowTitle(QString::fromLocal8Bit("请打开多视点图像"));//标题
	chooseData.setNameFilter("Images (*.bmp )");//设置默认打开类型
	chooseData.setFileMode(QFileDialog::ExistingFiles);//返回 多文件
	chooseData.setAcceptMode(QFileDialog::AcceptOpen);//文件对话框为打开类型
	chooseData.setDirectory(QString("F:\\test\\yasuo\\"));//初始根目录

	if (chooseData.exec() == QDialog::Accepted)//在exec踏步 直到返回结果
	{

		QStringList VideoList = chooseData.selectedFiles();
		auto video_name = VideoList[0];
		file_name = video_name.toStdString();//文件路径转换为string类型

		bool ifload = false;
		//ifload=mythread.InitThread(HWND(ui.label->winId()), file_name,2160,3840,50);//设置输出尺寸
		//ifload=mythread.InitThread(HWND(ui.label->winId()), file_name,1280,720,50);//设置输出尺寸
		ifload=mythread.InitThread(HWND(ui.label->winId()), file_name,1920,1080,50);//设置输出尺寸
		if (ifload)
		{
			ui.label->setText(QString::fromLocal8Bit("多视点图片已导入，可以播放！！"));
			ui.label->resize(640, 360);  
			play_start();//载入后 自动播放
		}
		else{
			QMessageBox::information(this, QString::fromLocal8Bit("错误"), QString::fromLocal8Bit("视频无法打开")); //提示说失败
		}
	}
}

void player::get_value()
{
	//mythread.pause=true;
	mythread.LineNum = float(ui.doubleSpinBox->value());//线长

	float temp = float(ui.doubleSpinBox_2->value());//倾角
	temp = temp / 180.0*3.141592653579;//化为弧度制
	temp = tan(temp);//求正切
	mythread.InclinationAngle = temp;//赋值

	mythread.MoveValue = float(ui.doubleSpinBox_3->value());//位移
	//mythread.pause = false;
}
void player::Reverse()
{
	//mythread.pause = true;
	mythread.ifReverse = !mythread.ifReverse;
	//mythread.pause = false;
}