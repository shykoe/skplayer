#include "skplayer.h"
#include "qfiledialog.h"
#include "sffmpeg.h"
#include "sAudioPlay.h"
#include "qfiledialog.h"
#include "qstring.h"
#include "qtableview.h"
#include "SplitVideo.h"
#include "qmessagebox.h"
#include <qmessagebox.h>
#include <QMenu>
#include <SplitVideo.h>
#define PAUSESTYLE "QPushButton{border-image: url(:/skplayer/Resources/pause_703px_1194928_easyicon.net.png);}"
#define PLAYSTYLE "QPushButton{border-image: url(:/skplayer/Resources/play_703px_1194928_easyicon.net.png);}"
static bool ispressSlider = false;
static bool isplay = true;

skplayer::skplayer(QWidget *parent)
	: QWidget(parent), VideoWidth(0), VideoHeight(0)
{
	ui.setupUi(this);
	//setMaximumSize(1366, 768);
	startTimer(40);
	setAttribute(Qt::WA_DeleteOnClose,true);

	_model = new SegTableModel();
	proxyModel = new QSortFilterProxyModel(this);
	proxyModel->setSourceModel(_model);
	proxyModel->setSortRole(Qt::EditRole);
	proxyModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
	proxyModel->setFilterKeyColumn(-1);
	ui.Seginfo->setModel(proxyModel);
	ui.Seginfo->setStyleSheet("selection-background-color:QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 rgb(152,202,104), stop: 0.25 #7fbb43, stop: 0.5 #6f9d3d,  stop: 0.7 #66b01e);");
	ui.Seginfo->horizontalHeader()->setStretchLastSection(true);
	ui.Seginfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.Seginfo->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.LogText->setReadOnly(true);
	ui.OutputDirEdit->setText(QCoreApplication::applicationDirPath());
	menu = new QMenu();
	QAction *toPlay = menu->addAction(QString::fromLocal8Bit("跳到此处播放"));
	QAction *splitAction_s = menu->addAction(QString::fromLocal8Bit("设置为起始点"));
	QAction *splitAction_e = menu->addAction(QString::fromLocal8Bit("设置为终点"));

	mythread = CaffeThread::Getcaffe();


	string model_file = "E:\\videocaffedata\\template_net.prototxt";
	string trained_file = "E:\\videocaffedata\\_iter_15000.caffemodel";
	string mean_file = "E:\\videocaffedata\\seg_leveldb_mean";
	string label_file = "synset_words.txt";
	ui.ModelEdit->setText(QString(QString::fromLocal8Bit(trained_file.c_str())));
	ui.ProtoEdit->setText(QString(QString::fromLocal8Bit(model_file.c_str())));
	ui.MeanEdit->setText(QString(QString::fromLocal8Bit(mean_file.c_str())));

	connect(ui.Seginfo, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(contextMenu(const QPoint)));
	connect(splitAction_s, &QAction::triggered, this, &skplayer::splitvideo_s);
	connect(splitAction_e, &QAction::triggered, this, &skplayer::splitvideo_e);
	connect(this->mythread, SIGNAL(CaffeInit()), this, SLOT(Caffed()));
	connect(this->mythread, SIGNAL(message(int, float)), this, SLOT(getmes(int, float)));
	connect(ui.InitCaffe, SIGNAL(clicked()), SLOT(InitCaffe()));
	connect(ui.AnalysisBt, SIGNAL(clicked()), this, SLOT(AnalysisMsg()));

	AddSegitem(11, 0.111);
	AddSegitem(11, 0.111);
	AddSegitem(11, 0.111);

}
void skplayer::Caffed()
{
	ui.LogText->append("init caffe success");
}
void skplayer::openFile(QString name)
{
	if (name.isEmpty())
		return;
	this->setWindowTitle(name);
	int totalMs = sffmpeg::Get()->Open(name.toLocal8Bit());
	if (!SplitVideo::Get()->isopen)
	{
		SplitVideo::Get()->OpenSource(name.toStdString());
	}
	if (totalMs <= 0)
	{
		QMessageBox::information(this, "err", "file open failed!");
		return;
	}
	sAudioPlay::Get()->sampleRate = sffmpeg::Get()->sampleRate;
	sAudioPlay::Get()->channel = sffmpeg::Get()->channel;
	sAudioPlay::Get()->sampleSize = 16;
	sAudioPlay::Get()->Start();
	char buf[1024] = { 0 };
	int min = (totalMs / 1000) / 60;
	int sec = (totalMs / 1000) % 60;
	sprintf(buf, "%03d:%02d", min, sec);
	ui.playTime1->setText(buf);
	isplay = false;
	play();
}
void skplayer::open()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择视频文件"));
	openFile(name);
}

skplayer::~skplayer()
{
	//isplay = false;
	printf("close");
	sffmpeg::Get()->isplay = false;
	sffmpeg::Get()->Close();
	//sffmpeg::Get()->isplay = false;
	//sffmpeg::Get()->Close();
	//sAudioPlay::Get()->Stop();
}

void skplayer::timerEvent(QTimerEvent * e)
{
	int min = (sffmpeg::Get()->pts / 1000) / 60;
	int sec = (sffmpeg::Get()->pts / 1000) % 60;
	char buf[1024] = { 0 };
	sprintf(buf, "%03d:%02d", min, sec);
	//printf(buf);
	ui.playTime1_2->setText(buf);

	if (sffmpeg::Get()->totalMs > 0)
	{
		float rate = (float)sffmpeg::Get()->pts / (float)sffmpeg::Get()->totalMs;
		if(!ispressSlider)
			ui.playslider->setValue(rate * 1000);
	}
}

void skplayer::resizeEvent(QResizeEvent * e)
{
	//ui.openGLWidget->resize(size());
	//ui.openButton->move(30, this->height() - 70);
	//ui.playButton->move(90, this->height() - 70);
	//ui.playTime1_2->move(150, this->height() - 60);
	//ui.playTime1->move(200, this->height() - 60);
	//ui.sp->move(190, this->height() - 60);
	//ui.playslider->move(240, this->height() - 60);
	//ui.playslider->resize(this->width() - 249, ui.playslider->height());
}

void skplayer::sliderPressed()
{
	ispressSlider = true;
}

void skplayer::sliderReleased()
{
	float pos = (float)ui.playslider->value() / (float)(ui.playslider->maximum() + 1);
	sffmpeg::Get()->Seek(pos);

	ispressSlider = false;

}

void skplayer::play()
{
	isplay = !isplay;
	sffmpeg::Get()->isplay = isplay;
	if (isplay)
	{
		ui.playButton->setStyleSheet(PAUSESTYLE);
	}
	else
	{
		ui.playButton->setStyleSheet(PLAYSTYLE);
	}
	//if (this->VideoWidth == 0 && this->VideoHeight == 0)
	//{
	//	this->VideoWidth = sffmpeg::Get()->getWidth();
	//	this->VideoHeight = sffmpeg::Get()->getHeight();
	//	resize(this->VideoWidth, this->VideoHeight );

	//}
}

void skplayer::AddSegitem(int stime, float score)
{
	segmentation *test = new segmentation(0, stime, score);
	_model->appendItem(test);
}
void skplayer::splitvideo_s()
{
	printf("%d\n", ui.Seginfo->currentIndex().row());
	if (startItem != -1)
	{
		ui.LogText->append(QString::fromLocal8Bit("已经设置过起始点"));
		_model->getItem(startItem)->setflag(segitem::Skip);
		startItem = ui.Seginfo->currentIndex().row();
		_model->getItem(ui.Seginfo->currentIndex().row())->setflag(segitem::Start);
	}
	startItem = ui.Seginfo->currentIndex().row();
	_model->getItem(ui.Seginfo->currentIndex().row())->setflag(segitem::Start);
	ui.LogText->append(QString::fromLocal8Bit("设置 %1 sec 为起点").arg(_model->getItem(ui.Seginfo->currentIndex().row())->truedata(1).toInt()));
}
void skplayer::splitvideo_e()
{
	printf("%d\n", ui.Seginfo->currentIndex().row());
	if (endItem != -1)
	{
		ui.LogText->append(QString::fromLocal8Bit("已经设置过终点"));
		_model->getItem(endItem)->setflag(segitem::Skip);
		endItem = ui.Seginfo->currentIndex().row();
		_model->getItem(ui.Seginfo->currentIndex().row())->setflag(segitem::End);
	}
	endItem = ui.Seginfo->currentIndex().row();
	_model->getItem(ui.Seginfo->currentIndex().row())->setflag(segitem::End);
	ui.LogText->append(QString::fromLocal8Bit("设置 %1 sec 为终点").arg(_model->getItem(ui.Seginfo->currentIndex().row())->truedata(1).toInt()));

}
void skplayer::contextMenu(const QPoint &pos)
{
	int row = ui.Seginfo->rowAt(pos.y());
	if (row != -1)
	{
		QAction *action = menu->exec(ui.Seginfo->mapToGlobal(pos));
		//printf("menu %d,%d" ,pos.x(), pos.y());
	}
	return;
}
void skplayer::SetModelFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择caffemodel文件"));
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.ModelEdit->setText(name);
}
void skplayer::SetProtoFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择proto文件"));
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.ProtoEdit->setText(name);
}
void skplayer::SetMeanFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择mean文件"));
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.MeanEdit->setText(name);
}
void skplayer::SetOutputFile()
{
	QString name = QFileDialog::getExistingDirectory(
		this, QString::fromLocal8Bit("选择存放位置")
	);
	if (name.isEmpty())
	{
		return;
	}
	printf("%s", name.toStdString().c_str());
	ui.OutputDirEdit->setText(name);
}
void skplayer::InitCaffe()
{
	if (cly != NULL)
		delete cly;
	auto modelfile = ui.ModelEdit->text();
	auto protofile = ui.ProtoEdit->text();
	auto meanfile = ui.MeanEdit->text();
	if (modelfile.isEmpty())
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::critical(this, tr("error"),
			tr("modelfile empty"),
			QMessageBox::Abort);
		return;
	}
	if (protofile.isEmpty())
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::critical(this, tr("error"),
			tr("protofile empty"),
			QMessageBox::Abort);
		return;
	}
	if (meanfile.isEmpty())
	{
		QMessageBox::StandardButton reply;
		reply = QMessageBox::critical(this, tr("error"),
			tr("meanfile empty"),
			QMessageBox::Abort);
		return;
	}
	ui.InitCaffe->setEnabled(false);
	cly = new caffe::Classifier(protofile.toStdString(), modelfile.toStdString(), meanfile.toStdString());
	//mythread->SetConf(protofile.toStdString(),modelfile.toStdString(), meanfile.toStdString());
	mythread->SetCaf(cly);
	this->mythread->start();
}
void skplayer::AnalysisMsg()
{
	QString pdata = ui.ScoreIp->text();
	bool flag = true;
	string suffixName = SplitVideo::Get()->suffixName;
	float score = pdata.toFloat(&flag);
	if (pdata.isEmpty() || !flag)
	{
		ui.LogText->append("invalid score input");
		return;
	}
	for (auto p = data.begin(); p != data.end(); p++)
	{
		float Pscore = std::get<1>(*p);
		if (Pscore > score)
		{
			AddSegitem(std::get<0>(*p), Pscore);
		}
	}
}
void skplayer::getmes(int time, float score)
{
	char buf[100];
	sprintf(buf, "%2d:%2d -- %f", time / 60, time % 60, score);
	//printf(buf, "%2d:%2d -- %f", time / 60, time % 60, score);
	ui.LogText->append(buf);
	data.push_back(std::make_tuple(time, score));
}