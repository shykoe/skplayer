#include "SplitVideo.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avfilter.lib")
float r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (float)r.num / (float)r.den;
}
SplitVideo::SplitVideo()
{
	buf = new char[4096];
	bufsize = 0;
	//memset(buf, 0, sizeof(buf));
	av_register_all();
}

bool SplitVideo::writeVideoHeader(AVFormatContext * ifmt_ctx, AVFormatContext * ofmt_ctx, string out_filename)
{
	AVOutputFormat *ofmt = NULL;
	AVCodec *codec;
	int ret;
	AVCodecContext *c;
	ofmt = ofmtCtx->oformat;

	for (int i = 0; i < ifmtCtx->nb_streams; i++) {

		//根据输入流创建输出流（Create output AVStream according to input AVStream）
		AVStream *in_stream = ifmtCtx->streams[i];
		codec = avcodec_find_encoder(in_stream->codecpar->codec_id);
		AVStream *out_stream = avformat_new_stream(ofmtCtx, codec);
		if (!out_stream) {
			ret = AVERROR_UNKNOWN;
			return false;
		}
		avcodec_parameters_from_context(out_stream->codecpar, in_stream->codec);
		if (ofmtCtx->oformat->flags & AVFMT_GLOBALHEADER)
			out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;
		out_stream->codecpar->codec_tag = 0;
	}
	if (!(ofmt->flags & AVFMT_NOFILE)) {
		ret = avio_open(&ofmtCtx->pb, out_filename.c_str(), AVIO_FLAG_WRITE);
		if (ret < 0) {
			return false;
		}
	}
	ret = avformat_write_header(ofmtCtx, NULL);
	if (ret < 0) {
		return false;
	}
	return true;
}


bool SplitVideo::OpenSource(std::string filepath,bool reload)
{
	QMutexLocker locker(&mutex);
	if (ifmtCtx && (!reload))
	{
		//sprintf(buf, "%s has loaded do not reload",filepath.c_str());
		//printf(buf);
		return true;
	}
	else
	{
		if (ifmtCtx)
			avformat_close_input(&ifmtCtx);
		if (int rev = avformat_open_input(&ifmtCtx, filepath.c_str(), 0, 0) != 0)
		{
			avformat_close_input(&ifmtCtx);
		}
		if (int ret = avformat_find_stream_info(ifmtCtx, 0)  < 0) {
			return false;
		}
		inputFileName = filepath;
		if (video_index = av_find_best_stream(ifmtCtx, AVMEDIA_TYPE_VIDEO, 0, -1, nullptr, 0) < 0)
		{
			return false;
		}
		if (audio_index = av_find_best_stream(ifmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0) < 0)
		{
			return false;
		}
		fps = r2d(ifmtCtx->streams[video_index]->r_frame_rate);
		if (fps <= 0)
		{
			return false;
		}
		sprintf(buf, "%s has loaded video_index--%d audio_index--%d fps--%f", inputFileName.c_str(), video_index, audio_index, fps);
		bufsize = sizeof(buf);
		//printf(buf);
		suffixName = filepath.substr(filepath.find_last_of('.') + 1);
		return true;
	}
}

SplitVideo::~SplitVideo()
{
	//delete[]buf;
}

bool SplitVideo::Split(unsigned int start, unsigned int duration, const string & outname)
{
	OpenSource(inputFileName);
	int ret;
	QMutexLocker locker(&mutex);
	AVPacket readPkt, splitKeyPacket;
	unsigned int startFrames = start * fps;
	unsigned int duraFrames = duration * fps;
	avformat_alloc_output_context2(&ofmtCtx, NULL, NULL, outname.c_str());
	if (!ofmtCtx) {
		return false;
	}
	if (!writeVideoHeader(ifmtCtx, ofmtCtx, outname))
	{
		return false;
	}
	vector<uint64_t> vecKeyFramePos;
	uint64_t frame_index = 0;
	uint64_t keyFrame_index = 0;
	int frameCount = 0;
	while (1)
	{
		++frame_index;
		ret = av_read_frame(ifmtCtx, &readPkt);
		if (ret < 0)
		{
			break;
		}
		//过滤，只处理视频流
		if (readPkt.stream_index == video_index) {

			++frameCount;
			if (readPkt.flags&AV_PKT_FLAG_KEY)
			{
				keyFrame_index = frame_index;
			}
			if (vecKeyFramePos.empty() && frameCount> startFrames)
			{
				vecKeyFramePos.push_back(keyFrame_index);
				frameCount = 0;
			}
			if (!vecKeyFramePos.empty() && (frameCount > duraFrames))
			{
				vecKeyFramePos.push_back(keyFrame_index);
				break;
			}
		}
		av_packet_unref(&readPkt);
	}
	avformat_close_input(&ifmtCtx);
	ifmtCtx = NULL;
	if ((ret = avformat_open_input(&ifmtCtx, inputFileName.c_str(), 0, 0)) < 0) {
		return false;
	}

	if ((ret = avformat_find_stream_info(ifmtCtx, 0)) < 0) {
		return false;
	}
	int number = 0;
	av_init_packet(&splitKeyPacket);
	splitKeyPacket.data = NULL;
	splitKeyPacket.size = 0;
	if (vecKeyFramePos.size() == 1) {
		vecKeyFramePos.push_back(frame_index);
	}
	int64_t startkeyFrame = vecKeyFramePos.front();
	int64_t endkeyFrame = vecKeyFramePos.back();
	frame_index = 0;
	bool flag = false;
	int64_t lastPts = 0;
	int64_t lastDts = 0;
	int64_t prePts = 0;
	int64_t preDts = 0;
	while (1)
	{
		++frame_index;
		ret = av_read_frame(ifmtCtx, &readPkt);
		if (ret < 0)
		{
			break;
		}
		av_packet_rescale_ts(&readPkt, ifmtCtx->streams[readPkt.stream_index]->time_base, ofmtCtx->streams[readPkt.stream_index]->time_base);


		//为分割点处的关键帧要进行拷贝
		if (frame_index == startkeyFrame)
		{
			flag = true;
			lastPts = readPkt.pts;
			lastDts = readPkt.dts;
		}
		if (readPkt.flags&AV_PKT_FLAG_KEY && (frame_index == startkeyFrame || frame_index == endkeyFrame))
		{
			av_copy_packet(&splitKeyPacket, &readPkt);

		}
		if (flag)
		{
			readPkt.pts -= lastPts;
			readPkt.dts -= lastDts;
			if (readPkt.pts < readPkt.dts)
			{
				readPkt.pts = readPkt.dts + 1;
			}
			ret = av_interleaved_write_frame(ofmtCtx, &readPkt);
			if (ret < 0) {
				//break;

			}
		}

		if (frame_index > endkeyFrame)
		{
			flag = false;
			av_write_trailer(ofmtCtx);
			avio_close(ofmtCtx->pb);
			avformat_close_input(&ifmtCtx);
			avformat_free_context(ofmtCtx);
			av_packet_unref(&readPkt);
			return true;
		}


		av_packet_unref(&readPkt);

	}
	av_packet_unref(&splitKeyPacket);
	av_write_trailer(ofmtCtx);
	avformat_close_input(&ifmtCtx);
	avio_close(ofmtCtx->pb);
	avformat_free_context(ofmtCtx);
	//vecResultName.push_back(temp_name);
	return true;
}
