#include "skplayer.h"
#include <QtWidgets/QApplication>
#include "sffmpeg.h"
#include <qaudiooutput.h>
#include <QtWidgets/QWidget>
int main(int argc, char *argv[])
{
	//QAudioOutput *out;
	//QAudioFormat fmt;
	//fmt.setSampleRate(48000);//1sec �ɼ�������
	//fmt.setSampleSize(16);//���������� 2^16��
	//fmt.setChannelCount(2);//��������
	//fmt.setCodec("audio/pcm");//������ʽ
	//fmt.setByteOrder(QAudioFormat::LittleEndian);
	//fmt.setSampleType(QAudioFormat::UnSignedInt);//�洢��ʽ
	//out = new QAudioOutput(fmt);
	//QIODevice *ad = out->start();
	
	
	QApplication a(argc, argv);
	skplayer w;
	w.show();
	printf("%s",sffmpeg::Get()->GetError().c_str());
	return a.exec();
}