#include "VideoWidget.h"
#include <qpainter.h>
#include "sffmpeg.h"
#include "VideoThread.h"
#include <string>
VideoWidget::VideoWidget(QWidget *e):QOpenGLWidget(e)
{
	//if (sffmpeg::Get()->Open("intoyou.mp4"))
	//	printf("ok");
	//else
	//{
	//	printf("error");
	//}
	startTimer(20);
	VideoThread::Get()->start();
}

void VideoWidget::paintEvent(QPaintEvent *e)
{
	static QImage *image = NULL;
	static int w = 0;
	static int h = 0;
	int test = 3;
	if (w != width() || h != height())
	{
		if (image)
		{
			delete image->bits();
			delete image;
			image = NULL;
		}
	}
	if (image == NULL)
	{
		uchar *buf = new uchar[width() * height() * 4];
		image = new QImage(buf, width(), height(), QImage::Format::Format_ARGB32);
	}
	sffmpeg::Get()->ToRGB((char*)image->bits(), width(), height());
	QPainter painter;
	painter.begin(this);
	painter.drawImage(QPoint(0, 0), *image);
	painter.end();
}

void VideoWidget::timerEvent(QTimerEvent * e)
{
	this->update();
}


VideoWidget::~VideoWidget()
{
}
