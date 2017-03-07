#include "skplayer.h"
#include <QtWidgets/QApplication>
#include "sffmpeg.h"
#include <qaudiooutput.h>
#include <QtWidgets/QWidget>
#include "caffeui.hpp"
#include<qstring.h>
int main(int argc, char *argv[])
{
	//QAudioOutput *out;
	//QAudioFormat fmt;
	//fmt.setSampleRate(48000);//1sec 采集的声音
	//fmt.setSampleSize(16);//声音的种类 2^16个
	//fmt.setChannelCount(2);//声道数量
	//fmt.setCodec("audio/pcm");//声音格式
	//fmt.setByteOrder(QAudioFormat::LittleEndian);
	//fmt.setSampleType(QAudioFormat::UnSignedInt);//存储格式
	//out = new QAudioOutput(fmt);
	//QIODevice *ad = out->start();
	
	
	QApplication a(argc, argv);
	//skplayer w;
	//w.show();
	caffeui s;
	s.show();
	/*QString test("11:212");
	if (test.contains(QRegularExpression("^\\d+:\\d{0,2}$")))
	{
		printf("ok");
	}*/
	//printf("%s",sffmpeg::Get()->GetError().c_str());
	return a.exec();
}
