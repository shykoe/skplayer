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
	skplayer sk;
	sk.show();
	caffeui s;
	s.show();
	/*SplitVideo *sp = SplitVideo::Get();
	sp->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");
	sp->Split(10, 10, "D:\\BaiduYunDownload\\test1.mp4");
	sp->Split(20, 20, "D:\\BaiduYunDownload\\test2.mp4");
	sp->Split(40, 20, "D:\\BaiduYunDownload\\test3.mp4");*/
	return a.exec();
}
