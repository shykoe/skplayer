#include "skplayer.h"
#include "qfiledialog.h"
#include "sffmpeg.h"
#include "sAudioPlay.h"
#include <qmessagebox.h>
#include <SplitVideo.h>
#define PAUSESTYLE "QPushButton{border-image: url(:/skplayer/Resources/pause_703px_1194928_easyicon.net.png);}"
#define PLAYSTYLE "QPushButton{border-image: url(:/skplayer/Resources/play_703px_1194928_easyicon.net.png);}"
static bool ispressSlider = false;
static bool isplay = true;

skplayer::skplayer(QWidget *parent)
	: QWidget(parent), VideoWidth(0), VideoHeight(0)
{
	ui.setupUi(this);
	setMaximumSize(1366, 768);
	startTimer(40);

}
void skplayer::openFile(QString name)
{
	if (name.isEmpty())
		return;
	this->setWindowTitle(name);
	int totalMs = sffmpeg::Get()->Open(name.toLocal8Bit());
	SplitVideo::Get()->OpenSource(name.toStdString());
	if (totalMs <= 0)
	{
		QMessageBox::information(this, "err", "file open failed!");
		return;
	}
	sAudioPlay::Get()->sampleRate = sffmpeg::Get()->sampleRate;
	sAudioPlay::Get()->channel = sffmpeg::Get()->channel;
	sAudioPlay::Get()->sampleSize = 16;
	sAudioPlay::Get()->Start();
	char buf[1024] = { 0 };
	int min = (totalMs / 1000) / 60;
	int sec = (totalMs / 1000) % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playTime1->setText(buf);
	isplay = false;
	play();
}
void skplayer::open()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择视频文件"));
	openFile(name);
}

skplayer::~skplayer()
{

}

void skplayer::timerEvent(QTimerEvent * e)
{
	int min = (sffmpeg::Get()->pts / 1000) / 60;
	int sec = (sffmpeg::Get()->pts / 1000) % 60;
	char buf[1024] = { 0 };
	sprintf(buf, "%03d:%02d", min, sec);
	//printf(buf);
	ui.playTime1_2->setText(buf);

	if (sffmpeg::Get()->totalMs > 0)
	{
		float rate = (float)sffmpeg::Get()->pts / (float)sffmpeg::Get()->totalMs;
		if(!ispressSlider)
			ui.playslider->setValue(rate * 1000);
	}
}

void skplayer::resizeEvent(QResizeEvent * e)
{
	ui.openGLWidget->resize(size());
	ui.openButton->move(30, this->height() - 70);
	ui.playButton->move(90, this->height() - 70);
	ui.playTime1_2->move(150, this->height() - 60);
	ui.playTime1->move(200, this->height() - 60);
	ui.sp->move(190, this->height() - 60);
	ui.playslider->move(240, this->height() - 60);
	ui.playslider->resize(this->width() - 249, ui.playslider->height());
}

void skplayer::sliderPressed()
{
	ispressSlider = true;
}

void skplayer::sliderReleased()
{
	float pos = (float)ui.playslider->value() / (float)(ui.playslider->maximum() + 1);
	sffmpeg::Get()->Seek(pos);

	ispressSlider = false;

}

void skplayer::play()
{
	isplay = !isplay;
	sffmpeg::Get()->isplay = isplay;
	if (isplay)
	{
		ui.playButton->setStyleSheet(PAUSESTYLE);
	}
	else
	{
		ui.playButton->setStyleSheet(PLAYSTYLE);
	}
	if (this->VideoWidth == 0 && this->VideoHeight == 0)
	{
		this->VideoWidth = sffmpeg::Get()->getWidth();
		this->VideoHeight = sffmpeg::Get()->getHeight();
		resize(this->VideoWidth, this->VideoHeight );

	}
}
