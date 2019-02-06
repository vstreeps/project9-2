#include <QtGui>
#include <QTimer>
#include <QMessageBox>
#include "mainwindow.h"

bool isPause = false;
bool isStarted = false;

int hours = 0;
int minutes = 0;
int seconds = 0;

MainWindow::MainWindow() {
	setWindowTitle(tr("Timer"));
	resize(700, 200);
	textLabel = new QLabel(this);
	textLabel->setText("00:00:00");
	textLabel->setGeometry(20, 150, 1200, 600);
	textLabel->setFont(QFont("Courier", 130, QFont::Bold));
	
	QPushButton *startButton = new QPushButton(tr("Start"), this);
	startButton->setGeometry(20, 5, 75, 30);
	startButton->setFont(QFont("Times", 18, QFont::Bold));
	connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClick()));
	
	QPushButton *stopButton = new QPushButton(tr("Stop"), this);
	stopButton->setGeometry(140, 5, 75, 30);
	stopButton->setFont(QFont("Times", 18, QFont::Bold));
	connect(stopButton, SIGNAL(clicked()), this, SLOT(stopButtonClick()));
	
	timeEdit = new QLineEdit(this);
	timeEdit->setGeometry(20, 100, 200, 20);
	
	myTimer = new QTimer(this);
	connect(myTimer, SIGNAL(timeout()), this, SLOT(runClock()));
}

void MainWindow::startButtonClick() {
	if(isStarted) {
		if(isPause) {
			isPause = false;
			myTimer->start(1000);
		}
		else {
			isPause = true;
			myTimer->stop();
		}
		isStarted = true;
	}
	else {
		mySeconds = (timeEdit->text()).toInt();
		seconds = mySeconds;

		hours = seconds / (60 * 60);
		seconds -= hours * 60 * 60;
		minutes = seconds / 60;
		seconds -= minutes * 60;

		QString strHours;
		strHours.setNum(hours);
		if(hours < 10)
			strHours = "0" + strHours;

		QString strMinutes;
		strMinutes.setNum(minutes);
		if(minutes < 10)
			strMinutes = "0" + strMinutes;

		QString strSeconds;
		strSeconds.setNum(seconds);
		if(seconds < 10)
			strSeconds = "0" + strSeconds;
    
		textLabel->setText(strHours + ":" + strMinutes + ":" + strSeconds);
		myTimer->start(1000);
		isStarted = true;
	}
}

void MainWindow::stopButtonClick() {
	isStarted = false;
	myTimer->stop();
	textLabel->setText("00:00:00");
}

void MainWindow::runClock() {
	mySeconds--;
	if( mySeconds < 1 )
		myTimer->stop();
	seconds = mySeconds;

	hours = seconds / (60 * 60);
	seconds -= hours * 60 * 60;
	minutes = seconds / 60;
	seconds -= minutes * 60;

	QString strHours;
	strHours.setNum(hours);
	if(hours < 10)
		strHours = "0" + strHours;

	QString strMinutes;
	strMinutes.setNum(minutes);
	if(minutes < 10)
		strMinutes = "0" + strMinutes;

	QString strSeconds;
	strSeconds.setNum(seconds);
	if(seconds < 10)
		strSeconds = "0" + strSeconds;
    
	textLabel->setText(strHours + ":" + strMinutes + ":" + strSeconds);
}
