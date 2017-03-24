#include "skplayer.h"
#include <QtWidgets/QApplication>
#include "sffmpeg.h"
#include <qaudiooutput.h>
#include <QtWidgets/QWidget>
#include "caffeui.hpp"
#include<qstring.h>
#include "SplitVideo.h"
int main(int argc, char *argv[])
{
	
	
	//QApplication a(argc, argv);
	//skplayer *sk = new skplayer;
	//sk->show();
	//caffeui s;
	//s.show();
	SplitVideo *sp = SplitVideo::Get();
	sp->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");
	if (!sp->init())
		return 1;
	int num = 0;
	int test = 20;
	while (1) {
		AVPacket pkt = sp->read();
		if (pkt.size <= 0)
			continue;
		IplImage* mat = sp->decode(&pkt, 300, 300, 10);
		av_packet_unref(&pkt);
		if (mat != NULL)
		{
			num++;
			cvSaveImage(std::string("test" + std::to_string(num) + ".jpg").c_str(), mat);
			cvReleaseImage(&mat);
			//(*sec)++;
		}
	}
	return 0;// a.exec();
}
