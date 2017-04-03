#include "sffmpeg.h"


#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib,"swresample.lib")
sffmpeg::sffmpeg()
{
	errorbuf[0] = '\0';
	av_register_all();
}

double r2d(AVRational r)
{
	return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}
int sffmpeg::Open(const char * path)
{
	Close();

	mutex.lock();
	if (int rev = avformat_open_input(&ic, path, 0, 0) != 0)
	{
		mutex.unlock();
		av_strerror(rev, errorbuf, sizeof(errorbuf));
		printf("open %s failed :%s", path, errorbuf);
		avformat_close_input(&ic);
		return 0;
	}
	totalMs = ic->duration / AV_TIME_BASE * 1000;

	for (int i = 0; i < ic->nb_streams; i++)
	{
		AVCodecParameters* enc = ic->streams[i]->codecpar;
		if (enc->codec_type == AVMEDIA_TYPE_VIDEO)//ÊÓÆµÁ÷
		{
			videoStream = i;
			fps = r2d(ic->streams[videoStream]->avg_frame_rate);
			AVCodec* codec = avcodec_find_decoder(enc->codec_id);
			videoCtx = avcodec_alloc_context3(codec);
			avcodec_parameters_to_context(videoCtx, enc);

			int rel = avcodec_open2(videoCtx, codec, NULL);
			if (rel != 0)
			{
				mutex.unlock();
				av_strerror(rel, errorbuf, sizeof(errorbuf));
				return 0;
			}
		}
		else if (enc->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audioStream = i;
			//AVStream* audio_st = ic->streams[audioStream];
			AVCodec* audioCodec = avcodec_find_decoder(enc->codec_id);
			audioCtx = avcodec_alloc_context3(audioCodec);
			avcodec_parameters_to_context(audioCtx, enc);
			if (avcodec_open2(audioCtx, audioCodec, NULL) < 0)
			{
				mutex.unlock();
				return 0;
			}
			this->sampleRate = audioCtx->sample_rate;
			this->channel = audioCtx->channels;
			switch (audioCtx->sample_fmt)
			{
			case AV_SAMPLE_FMT_S16:         ///< signed 16 bits
				this->sampleSize = 16;
				break;
			case AV_SAMPLE_FMT_S32:       ///< signed 32 bits
				this->sampleSize = 32;
			default:
				break;
			}
			printf("audiostream:%d audio sample rate:%d sample size:%d chanle£º%d\n",
				this->audioStream,this->sampleRate, this->sampleSize, this->channel);
		}
	}
	isexist = true;
	mutex.unlock();
	return totalMs;
}

void sffmpeg::Close()
{
	mutex.lock();
	if (ic)
	{
		avformat_close_input(&ic);
	}
	if (yuv)
	{
		av_frame_free(&yuv);
	}
	if (aCtx)
	{
		swr_free(&aCtx);
		
	}
	if (cCtx)
	{
		sws_freeContext(cCtx);
		cCtx = NULL;
	}
	if (videoCtx)
	{
		avcodec_free_context(&videoCtx);
	}
	if (audioCtx)
	{
		avcodec_free_context(&audioCtx);
	}
	mutex.unlock();
 
}

AVPacket sffmpeg::Read()
{
	AVPacket pkt;
	memset(&pkt, 0, sizeof(AVPacket));

	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return pkt;
	}
	int err = av_read_frame(ic, &pkt);
	if (err != 0)
	{
		av_strerror(err, errorbuf, sizeof(errorbuf));
	}
	mutex.unlock();
	return pkt;

}

int sffmpeg::Decode(const AVPacket * pkt)
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return -1;
	}
	if (yuv == NULL)
	{
		yuv = av_frame_alloc();
	}
	if (pcm == NULL)
	{
		pcm = av_frame_alloc();
	}
	AVFrame* frame = yuv;
	AVCodecContext* cctx = videoCtx;
	if (pkt->stream_index == audioStream)
	{
		frame = pcm;
		cctx = audioCtx;
		//printf("%d", pkt->stream_index);
	}
	else if (pkt->stream_index == videoStream)
	{
		frame = yuv;
		cctx = videoCtx;
		//printf("video %d", pkt->stream_index);
	}
	int rel = avcodec_send_packet(cctx, pkt);
	if (rel != 0)
	{
		mutex.unlock();
		return -1;
	}
	rel = avcodec_receive_frame(cctx, frame);
	if (rel != 0)
	{
		mutex.unlock();
		return -1;
	}
	mutex.unlock();
	int local_pts = frame->pts * r2d(ic->streams[pkt->stream_index]->time_base)*1000;
	if (pkt->stream_index == audioStream) this->pts = local_pts;
	return local_pts;
}

bool sffmpeg::Seek(float rate)
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return false;
	}
	int64_t stamp = 0;
	stamp = rate * ic->streams[videoStream]->duration;
	int rel = av_seek_frame(ic, videoStream, stamp, AVSEEK_FLAG_BACKWARD | AVSEEK_FLAG_FRAME);
	avcodec_flush_buffers(videoCtx);
	if (rel < 0)
	{
		mutex.unlock();
		return false;
	}
	pts = stamp * r2d(ic->streams[videoStream]->time_base) * 1000;
	mutex.unlock();
	return false;
}



std::string sffmpeg::GetError()
{
	mutex.lock();
	std::string re = this->errorbuf;
	mutex.unlock();
	return re;
}

int sffmpeg::getWidth() const
{
	if (videoCtx)
		return videoCtx->width;
	else
		return 0;
}

int sffmpeg::getHeight() const
{
	if (videoCtx)
		return videoCtx->height;
	else
		return 0;
}


sffmpeg::~sffmpeg()
{
}
int sffmpeg::ToPCM(char * out)
{
	mutex.lock();
	if (!ic || !pcm || !out || !audioCtx)
	{
		mutex.unlock();
		return -1;
	}
	if (aCtx == NULL)
	{
		aCtx = swr_alloc();
		swr_alloc_set_opts(aCtx, audioCtx->channel_layout,
			AV_SAMPLE_FMT_S16, audioCtx->sample_rate, audioCtx->channels, audioCtx->sample_fmt, audioCtx->sample_rate, 0, NULL);
		swr_init(aCtx);
	}
	uint8_t *data[1];
	data[0] = (uint8_t *)out;
	int len = swr_convert(aCtx, data, 10000, 
		(const uint8_t **)pcm->data, pcm->nb_samples);
	if (len <= 0)
	{
		mutex.unlock();
		return 0;
	}
	int outsize = av_samples_get_buffer_size(NULL, audioCtx->channels,
		pcm->nb_samples, AV_SAMPLE_FMT_S16, 0);
	mutex.unlock();
	return outsize;
}
int sffmpeg::GetPts(const AVPacket * pkt)
{
	mutex.lock();
	if (!ic)
	{
		mutex.unlock();
		return -1;
	}
	int local_pts = pkt->pts * r2d(ic->streams[pkt->stream_index]->time_base) * 1000;
	mutex.unlock();
	return local_pts;
}
bool sffmpeg::ToRGB( char * out, int outwidth, int outheight)
{
	mutex.lock();
	if (!ic || !yuv || yuv->linesize[0] <= 0)
	{
		mutex.unlock();
		return false;
	}

	cCtx = sws_getCachedContext(cCtx, videoCtx->width, videoCtx->height,
		videoCtx->pix_fmt, outwidth, outheight, AV_PIX_FMT_BGRA, SWS_BICUBIC, NULL, NULL, NULL);
	if (!cCtx)
	{	
		mutex.unlock();
		return false;
	}
	uint8_t *data[AV_NUM_DATA_POINTERS] = { 0 };
	data[0] = (uint8_t*)out;
	int linesize[AV_NUM_DATA_POINTERS] = { 0 };
	linesize[0] = outwidth * 4;
	int h = sws_scale(cCtx, yuv->data, yuv->linesize, 0, videoCtx->height,
		data, linesize
	);
	mutex.unlock();
	//printf("%d", h);
	return true;
}
