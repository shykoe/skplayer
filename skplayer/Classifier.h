#pragma once
#include "qstring.h"
#include "qmutex.h"
#include <QMutexLocker> 
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale\swscale.h>
#include <libswresample/swresample.h>
}
class Classifier
{
public:
	Classifier();
	bool Open(std::string file);
	virtual ~Classifier();
private:
	int totalMs;
	int video_index;
	QMutex mutex;
	AVFormatContext *ic = NULL;
	AVCodecContext* videoCtx = NULL;
};

