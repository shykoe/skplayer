#include "SplitVideo.h"

#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "avdevice.lib")
#pragma comment(lib, "avfilter.lib")
#pragma comment(lib, "postproc.lib  ")
#pragma comment(lib, "swresample.lib")
#pragma comment(lib, "swscale.lib   ")
#pragma comment(lib, "opencv_highgui310d.lib")
#pragma comment(lib, "opencv_core310d.lib")
#pragma comment(lib,"opencv_imgproc310d.lib")
#pragma comment(lib,"opencv_imgcodecs310d.lib")
static int num = 0;
float r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (float)r.num / (float)r.den;
}
SplitVideo::SplitVideo()
	:isopen(false),readysp(true)
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


bool SplitVideo::init()
{
	QMutexLocker locker(&mutex);
	readysp = false;
	//opendecodec
	if (codePar == NULL)
		return false;
	codec = avcodec_find_decoder(codePar->codec_id);
	if (codec == NULL)
	{
		return false;
	}
	codeCtx = avcodec_alloc_context3(codec);
	if (codeCtx == NULL)
	{
		return false;
	}
	if (avcodec_parameters_to_context(codeCtx, codePar) < 0)
	{
		return false;
	}
	if (avcodec_open2(codeCtx, codec, NULL) < 0)
	{
		return false;
	}
	int psize = codePar->width* codePar->height;
	//packet = (AVPacket*)malloc(sizeof(AVPacket));
	//if (av_new_packet(packet, psize) != 0)
	//{
	//	return false;
	//}

	
	return true;
}

AVPacket SplitVideo::read(int* flag)
{
	QMutexLocker locker(&mutex);
	AVPacket packet;
	memset(flag, 0, sizeof(int));
	*flag = av_read_frame(ifmtCtx, &packet);
	return packet;
}

IplImage* SplitVideo::decode(AVPacket* pkt, int width, int height, int* timestamp, int sec)
{
	QMutexLocker locker(&mutex);
	
	if (pkt->stream_index != video_index)
	{
		return NULL;
	}
	num++;
	if (frame == NULL)
	{
		frame = av_frame_alloc();
	}
	if (avcodec_send_packet(codeCtx, pkt) != 0)
	{
		return  NULL;
	}
	if (int rel = avcodec_receive_frame(codeCtx, frame) != 0)
	{
		printf("解码错误\n");
		return  NULL;
	}
	if (sec && (num%sec) != 0)
	{
		return NULL;
	}
	int pts = frame->pts *  r2d(ifmtCtx->streams[video_index]->time_base);
	memset(timestamp, 0, sizeof(int));
	*timestamp = pts;
	//printf("time-%d-%d\n", pts / 60, pts % 60);
	//height = (codeCtx->height * width / codeCtx->width);
	img_convert_ctx = sws_getCachedContext(img_convert_ctx, codeCtx->width, codeCtx->height, codeCtx->pix_fmt, width, height, AV_PIX_FMT_BGR24, SWS_BICUBIC, NULL, NULL, NULL);
	if (img_convert_ctx == NULL)
	{
		return NULL;
	}
	//uint8_t* out_bufferBRG = new uint8_t[av_image_get_buffer_size(AV_PIX_FMT_BGR24, width, height, 1)]();
	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };

	linesize[0] = width * 3;
	IplImage* PcvFrame = cvCreateImage(cvSize(width, height), 8, 3);
	data[0] = (uint8_t*)PcvFrame->imageData;
	sws_scale(img_convert_ctx, (const uint8_t* const*)frame->data, frame->linesize, 0, codeCtx->height, data, linesize);
	return PcvFrame;

	
}

bool SplitVideo::OpenSource(std::string path2file,bool reload)
{
	QMutexLocker locker(&mutex);
	if (ifmtCtx && (!reload))
	{
		//sprintf(buf, "%s has loaded do not reload",filepath.c_str());
		//printf(buf);
		isopen = true;
		return true;
	}
	else
	{
		if (ifmtCtx)
			avformat_close_input(&ifmtCtx);
		if (int rev = avformat_open_input(&ifmtCtx, path2file.c_str(), 0, 0) != 0)
		{
			avformat_close_input(&ifmtCtx);
		}
		totalSec = ifmtCtx->duration * AV_TIME_BASE;
		if (int ret = avformat_find_stream_info(ifmtCtx, 0)  < 0) {
			return false;
		}
		inputFileName = path2file;
		path = path2file.substr(0, path2file.find_last_of('\\')+1);
		if (video_index = av_find_best_stream(ifmtCtx, AVMEDIA_TYPE_VIDEO, 0, -1, nullptr, 0) < 0)
		{
			return false;
		}
		codePar = ifmtCtx->streams[video_index]->codecpar;
		if (audio_index = av_find_best_stream(ifmtCtx, AVMEDIA_TYPE_AUDIO, -1, -1, NULL, 0) < 0)
		{
			return false;
		}
		fps = r2d(ifmtCtx->streams[video_index]->r_frame_rate);
		if (fps <= 0)
		{
			return false;
		}
		isopen = true;
		sprintf(buf, "%s has loaded video_index--%d audio_index--%d fps--%f", inputFileName.c_str(), video_index, audio_index, fps);
		bufsize = sizeof(buf);
		//printf(buf);
		suffixName = path2file.substr(path2file.find_last_of('.') + 1);
		//readysp = true;
		return true;
	}
}

SplitVideo::~SplitVideo()
{
	delete[]buf;
}

bool SplitVideo::Split(unsigned int start, unsigned int duration, const string & outname)
{
	if (!readysp)
		return false;
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
	av_packet_unref(&readPkt);
	av_packet_unref(&splitKeyPacket);
	av_write_trailer(ofmtCtx);
	avformat_close_input(&ifmtCtx);
	avio_close(ofmtCtx->pb);
	avformat_free_context(ofmtCtx);
	//vecResultName.push_back(temp_name);
	return true;
}
