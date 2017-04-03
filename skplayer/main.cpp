#include "skplayer.h"
#include <QtWidgets/QApplication>
#include "sffmpeg.h"
#include <qaudiooutput.h>
#include <QtWidgets/QWidget>
#include "caffeui.hpp"
#include<qstring.h>
#include "SplitVideo.h"
#ifdef STRICT
#undef STRICT
#include"Classifier.h"
#endif
int main(int argc, char *argv[])
{
	//::google::InitGoogleLogging(argv[0]);
	//string model_file = "E:\\videocaffedata\\template_net.prototxt";
	//string trained_file = "E:\\videocaffedata\\_iter_15000.caffemodel";
	//string mean_file = "E:\\videocaffedata\\seg_leveldb_mean";
	//string label_file = "synset_words.txt";
	//
	//caffe::Classifier classifier(model_file, trained_file, mean_file);
	//string file = "E:\\videocaffedata\\img142.jpg";
	//cv::Mat img = cv::imread(file, -1);
	//auto predictions = classifier.Classify(img);
	//for (auto i : predictions)
	//{
	//	std::cout << i << std::endl;
	//}
	//getchar();
	QApplication a(argc, argv);
	skplayer *sk = new skplayer;
	sk->show();
	caffeui s;
	s.show();
	//qDebug("123");
	//SplitVideo *sp = SplitVideo::Get();
	//sp->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");
	//if (!sp->init())
	//	return 1;
	//int num = 0;
	//int test = 20;
	//while (1) {
	//	AVPacket pkt = sp->read();
	//	if (pkt.size <= 0)
	//		continue;
	//	IplImage* mat = sp->decode(&pkt, 300, 300, 10);
	//	av_packet_unref(&pkt);
	//	if (mat != NULL)
	//	{
	//		num++;
	//		cv::Mat cvmt = cv::cvarrToMat(mat);
	//		//cvSaveImage(std::string("test" + std::to_string(num) + ".jpg").c_str(), mat);
	//		auto predictions = classifier.Classify(cvmt);
	//		for (auto i : predictions)
	//		{
	//			std::cout << i << std::endl;
	//		}
	//		cvReleaseImage(&mat);
	//		//(*sec)++;
	//	}
	//}
	return a.exec();
}
