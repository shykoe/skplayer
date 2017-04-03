#pragma once
#include <string>
#include <qmutex.h>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale\swscale.h>
#include <libswresample/swresample.h>
}
class sffmpeg
{
public:
	static sffmpeg* Get()
	{
		static sffmpeg ff1;
		return &ff1;
	}

	int Open(const char* path);

	void Close();

	//return value must be freed!
	AVPacket Read();
	
	int Decode(const AVPacket *pkt);

	bool Seek(float rate);

	bool ToRGB(char *out, int outwidth, int outheight);

	int ToPCM(char* out);
	//return ms  
	int GetPts(const AVPacket* pkt);

	virtual ~sffmpeg();

	inline int GetVideoStream() { return videoStream; }
	inline int GetAudioStream() { return audioStream; }
	int  getWidth() const;
	int getHeight() const;
	std::string GetError();
	int totalMs;
	double fps = 0;
	int pts = 0;
	bool isexist = false;
	bool isplay = false;
	int sampleRate = 48000;
	int sampleSize = 16;
	int channel = 2;
	//inline AVFormatContext* getic() {return ic; };
	inline std::string GetFileName() { if (ic) return ic->filename; }
protected:
	char errorbuf[1024] = { 0 };
	AVFrame* yuv = NULL;
	AVFrame* pcm = NULL;
	QMutex mutex;
	AVCodecContext* videoCtx = NULL;
	AVCodecContext* audioCtx = NULL;
	int videoStream;
	int audioStream;
	AVFormatContext *ic = NULL;
	SwsContext *cCtx = NULL;
	SwrContext *aCtx = NULL;
	sffmpeg();
};

