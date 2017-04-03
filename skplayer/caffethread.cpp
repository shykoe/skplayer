#include "caffethread.h"
#include "SplitVideo.h"
CaffeThread::CaffeThread(QObject *parent)
	: QThread(parent)
{
}

CaffeThread::~CaffeThread()
{

}
void CaffeThread::SetConf(std::string model_file, std::string trained_file, std::string mean_file)
{
	this->model_file = model_file;
	this->trained_file = trained_file;
	this->mean_file = mean_file;
}
void CaffeThread::SetCaf(caffe::Classifier* cf)
{
	cly = cf;
}
void CaffeThread::run()
{
	SplitVideo *sp = SplitVideo::Get();
	int num = 0;
	int test = 20;
	if (!sp->init())
		return ;
	while (1) {
		int flag = 0;
		AVPacket pkt = sp->read(&flag);
		if (flag < 0)
			break;
		if (pkt.size <= 0)
			continue;
		int time = 0;
		IplImage* mat = sp->decode(&pkt, 300, 300, &time, 10);
		av_packet_unref(&pkt);
		if (mat != NULL)
		{
			num++;
			cv::Mat cvmt = cv::cvarrToMat(mat);
			std::vector<float> predictions = cly->Classify(cvmt);
			emit message(time, predictions.back());
			cvReleaseImage(&mat);

		}
	}

}

