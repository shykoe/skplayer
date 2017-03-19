#include "Classifier.h"



Classifier::Classifier()
{
}

bool Classifier::Open(std::string file)
{
	QMutexLocker lk(&mutex);
	if (int rev = avformat_open_input(&ic, file.c_str(), 0, 0) != 0)
	{
		avformat_close_input(&ic);
		return false;
	}
	totalMs = ic->duration / AV_TIME_BASE * 1000;
	if (video_index = av_find_best_stream(ic, AVMEDIA_TYPE_VIDEO, 0, -1, nullptr, 0) < 0)
	{
		avformat_close_input(&ic);
		return false;
	}
	AVCodecParameters* enc = ic->streams[video_index]->codecpar;
	AVCodec* codec = avcodec_find_decoder(enc->codec_id);
	videoCtx = avcodec_alloc_context3(codec);
	avcodec_parameters_to_context(videoCtx, enc);
	int rel = avcodec_open2(videoCtx, codec, NULL);

	if (rel != 0)
	{
		avformat_close_input(&ic);
		return 0;
	}
	return 0;
}


Classifier::~Classifier()
{
}
