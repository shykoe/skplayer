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
	
	
	QApplication a(argc, argv);
	//skplayer *sk = new skplayer;
	//sk->show();
	//caffeui s;
	//s.show();
	SplitVideo *sp = SplitVideo::Get();
	sp->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");
	sp->init();
	int num = 0;
	while (sp->read())
	{
		cv::Mat mat = sp->decode(300,300,5);
		if (!mat.empty())
		{
			num++;
			cv::imwrite("test"+std::to_string(num)+".jpg", mat);
		}
	}
	return a.exec();
}
