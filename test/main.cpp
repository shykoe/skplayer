#include"head.h"
#pragma comment(lib, "avformat.lib")
#pragma comment(lib, "avutil.lib")
#pragma comment(lib, "avcodec.lib")
#pragma comment(lib, "swscale.lib")
#pragma comment(lib,"swresample.lib")
void main()
{
	av_register_all();
	AVFormatContext *ic = NULL;
	char* path = "E:\\badapple_video.avi";
	int rev = avformat_open_input(&ic, path, 0, 0);
	avformat_find_stream_info(ic, NULL);
	if (ic->duration == AV_NOPTS_VALUE)
	{
		printf("error\n");
	}
	int64_t tot = ic->duration / AV_TIME_BASE * 1000;
	//for (int i = 0; i < ic->nb_streams; i++)
	//{
	//	AVCodecParameters* enc = ic->streams[i]->codecpar;
	//	enc->
	//}
	printf("%lld", tot);
	getchar();
}