#include "VideoThread.h"
#include "sAudioPlay.h"
#include"sffmpeg.h"
#include<list>
//static std::list<AVPacket> videos;
static int apts = -1;
VideoThread::VideoThread():isexited(false)
{

}

void VideoThread::run()
{
	char out[10000] = { 0 };
	while (!isexited)
	{
		if (!sffmpeg::Get()->isplay)
		{
			msleep(30);
			continue;
		}

		int free = sAudioPlay::Get()->GetFree();
		if (free < 10000)
		{
			msleep(1);
			continue;
		}

		AVPacket pkt = sffmpeg::Get()->Read();
		if (pkt.size <= 0)
		{
			msleep(1);
			continue;
		}
		if (pkt.stream_index == sffmpeg::Get()->GetAudioStream())
		{
			apts = sffmpeg::Get()->Decode(&pkt);
			av_packet_unref(&pkt);
			int len = sffmpeg::Get()->ToPCM(out);
			sAudioPlay::Get()->Write(out, len);
			continue;
		}
		if (pkt.stream_index != sffmpeg::Get()->GetVideoStream())
		{
			av_packet_unref(&pkt);
			continue;
		}
		//videos.push_back(pkt);
		sffmpeg::Get()->Decode(&pkt);
		av_packet_unref(&pkt);
		//if(sffmpeg::Get()->fps >0)
			//msleep(1000 / sffmpeg::Get()->fps);
	}
}


VideoThread::~VideoThread()
{
	isexited = true;
}
