#pragma once
#include <string>
#include <qmutex.h>
#include <vector>
#include <QMutexLocker> 
#include <tuple>
#include <queue>
extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
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
	bool OpenSource(std::string FileName, bool reload = true);
	~SplitVideo();
	bool Split(unsigned int start, unsigned int duration, const string& outname);
	char* getbuf() { return buf; }
	size_t bufsize;
	//bool addTask(unsigned start, unsigned duration,string filename);
private:

	SplitVideo();
	uint64_t splitFrameSize;
	string suffixName;
	float fps = 0;
	bool isInit;
	string inputFileName;
	string outputFileName;
	int video_index, audio_index;
	AVFormatContext *ifmtCtx = NULL, *ofmtCtx = NULL;
	bool writeVideoHeader(AVFormatContext *ifmt_ctx, AVFormatContext *ofmt_ctx, string out_filename);
	QMutex mutex;
	char* buf;
};
