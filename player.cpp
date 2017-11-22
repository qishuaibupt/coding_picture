#include "player.h"

player::player(QWidget *parent)
	: QMainWindow(parent)
{
	pause = false;
	ui.setupUi(this);

	ui.label->setText(QString::fromLocal8Bit("������ V1.0"));//��ֹ�������� fromLocal8bit
	ui.label->setFont(QFont("Times", 30));
	ui.label->setFrameShape(QFrame::Box); //�߿���ʽ

	QPalette m_nColor;
	ui.label->setAutoFillBackground(true);//important ���ô����Զ���䱳��
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
	mythread.stop();//��������
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
		//ui.play->setText(QString::fromLocal8Bit("��ͣ"));
	//}
	//else{//pause
		//mythread.pauseThread(); 
		//ui.play->setText(QString::fromLocal8Bit("����"));
	//}
}


void player::load_video()
{
	QFileDialog chooseData;

	chooseData.setWindowTitle(QString::fromLocal8Bit("��򿪶��ӵ�ͼ��"));//����
	chooseData.setNameFilter("Images (*.bmp )");//����Ĭ�ϴ�����
	chooseData.setFileMode(QFileDialog::ExistingFiles);//���� ���ļ�
	chooseData.setAcceptMode(QFileDialog::AcceptOpen);//�ļ��Ի���Ϊ������
	chooseData.setDirectory(QString("F:\\test\\yasuo\\"));//��ʼ��Ŀ¼

	if (chooseData.exec() == QDialog::Accepted)//��exec̤�� ֱ�����ؽ��
	{

		QStringList VideoList = chooseData.selectedFiles();
		auto video_name = VideoList[0];
		file_name = video_name.toStdString();//�ļ�·��ת��Ϊstring����

		bool ifload = false;
		//ifload=mythread.InitThread(HWND(ui.label->winId()), file_name,2160,3840,50);//��������ߴ�
		//ifload=mythread.InitThread(HWND(ui.label->winId()), file_name,1280,720,50);//��������ߴ�
		ifload=mythread.InitThread(HWND(ui.label->winId()), file_name,1920,1080,50);//��������ߴ�
		if (ifload)
		{
			ui.label->setText(QString::fromLocal8Bit("���ӵ�ͼƬ�ѵ��룬���Բ��ţ���"));
			ui.label->resize(640, 360);  
			play_start();//����� �Զ�����
		}
		else{
			QMessageBox::information(this, QString::fromLocal8Bit("����"), QString::fromLocal8Bit("��Ƶ�޷���")); //��ʾ˵ʧ��
		}
	}
}

void player::get_value()
{
	//mythread.pause=true;
	mythread.LineNum = float(ui.doubleSpinBox->value());//�߳�

	float temp = float(ui.doubleSpinBox_2->value());//���
	temp = temp / 180.0*3.141592653579;//��Ϊ������
	temp = tan(temp);//������
	mythread.InclinationAngle = temp;//��ֵ

	mythread.MoveValue = float(ui.doubleSpinBox_3->value());//λ��
	//mythread.pause = false;
}
void player::Reverse()
{
	//mythread.pause = true;
	mythread.ifReverse = !mythread.ifReverse;
	//mythread.pause = false;
}