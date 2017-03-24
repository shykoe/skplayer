#pragma once
#include <string>
#include <qmutex.h>
#include <vector>
#include <QMutexLocker> 
#include <tuple>
#include <queue>
#include "opencv/cv.h"
#include "opencv2/opencv.hpp"
#include "opencv/cxcore.h"
#include "opencv/highgui.h"
extern "C"
{
#include <libavcodec/avcodec.h>
#include "libswscale/swscale.h"
#include <libswresample/swresample.h>
#include <libavformat/avformat.h>
#include"libavutil/imgutils.h"
}
using std::vector;
using std::string;
using std::tuple;
class SplitVideo
{
public:


	static SplitVideo* Get() {
		static SplitVideo spv;
		return &spv;
	}
	/*
	init for extract cv::mat
	*/
	bool init();
	/*
	read every step frames 
	return :success on true,error or end on false
	*/
	AVPacket read();
	/*
	decode to a img with width and height 
	step means it decode every step sec img ,default value 0 means decode every frame  
	return empty mat on failure
	*/
	IplImage* decode(AVPacket* pkt, int width, int height, int sec=10);
	bool OpenSource(std::string FileName, bool reload = true);
	~SplitVideo();
	bool Split(unsigned int start, unsigned int duration, const string& outname);
	char* getbuf() { return buf; }
	size_t bufsize;
	bool isopen = false;
	std::string& getpath()  { return path; }
	bool readysp;
	//bool addTask(unsigned start, unsigned duration,string filename);
private:
	int framenum = 0;
	SplitVideo();
	uint64_t splitFrameSize;
	string suffixName;
	float fps = 0;
	string inputFileName;
	string path;
	int video_index, audio_index;
	AVFormatContext *ifmtCtx = NULL, *ofmtCtx = NULL;
	AVCodec *codec = NULL;
	AVCodecParameters *codePar = NULL;
	AVCodecContext *codeCtx = NULL;
	AVFrame *frame = NULL;
	//AVPacket *packet = NULL;
	SwsContext *img_convert_ctx = NULL;
	bool writeVideoHeader(AVFormatContext *ifmt_ctx, AVFormatContext *ofmt_ctx, string out_filename);
	QMutex mutex;
	char* buf;
};
