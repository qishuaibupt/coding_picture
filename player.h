#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_player.h"

#include <QFileDialog>
#include <QMessageBox>

#include"play_thread.h"
#include<math.h>
using namespace Qt;

class player : public QMainWindow
{
	Q_OBJECT

public:
	player(QWidget *parent = Q_NULLPTR);
	~player();
	
	playThread mythread;
	string file_name;

	int width=0;
	int height=0;
	int view_number = 50;

	bool pause;

private:
	Ui::playerClass ui;

public slots:
	void play_start();
	void load_video();
	void get_value();
	void Reverse();
	void esc();
};
