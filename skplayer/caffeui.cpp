#include "caffeui.hpp"
#include "qfiledialog.h"
#include "qstring.h"
#include "qtableview.h"
#include "SplitVideo.h"
#include "qmessagebox.h"
#include <QMenu>

caffeui::caffeui(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
	//ui.Seginfo->
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
	//splitAction->setCheckable(true);
	mythread = CaffeThread::Getcaffe();


	string model_file = "E:\\videocaffedata\\template_net.prototxt";
	string trained_file = "E:\\videocaffedata\\_iter_15000.caffemodel";
	string mean_file = "E:\\videocaffedata\\seg_leveldb_mean";
	string label_file = "synset_words.txt";
	ui.ModelEdit->setText(QString(QString::fromLocal8Bit(trained_file.c_str())));
	ui.ProtoEdit->setText(QString(QString::fromLocal8Bit(model_file.c_str())));
	ui.MeanEdit->setText(QString(QString::fromLocal8Bit(mean_file.c_str())));
	

	connect(this->mythread, SIGNAL(CaffeInit()), this, SLOT(Caffed()));
	connect(this->mythread, SIGNAL(message(int,float)), this, SLOT(getmes(int, float)));
	connect(ui.Seginfo, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(contextMenu(const QPoint)));
	connect(splitAction_s, &QAction::triggered, this, &caffeui::splitvideo_s);
	connect(splitAction_e, &QAction::triggered, this, &caffeui::splitvideo_e);
	connect(ui.InitCaffe, SIGNAL(clicked()), SLOT(InitCaffe()));
	connect(ui.AnalysisBt, SIGNAL(clicked()), this, SLOT(AnalysisMsg()));


	//debug
	AddSegitem( 11, 0.111);
	AddSegitem(11, 0.111);
	AddSegitem(11, 0.111);

	//SplitVideo::Get()->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");


	//startTimer(40);
	
}
void caffeui::toPlay()
{
	if (!sffmpeg::Get()->isexist)
	{
		ui.LogText->append(QString::fromLocal8Bit("播放器或者视频文件未打开"));
		return;
	}

}
void caffeui::splitvideo_e()
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
	ui.LogText->append(QString::fromLocal8Bit("设置 %1 sec 为终点").arg(_model->getItem(ui.Seginfo->currentIndex().row())->truedata(1).toInt()) );

}
void caffeui::splitvideo_s()
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
void caffeui::contextMenu(const QPoint &pos)
{
	int row = ui.Seginfo->rowAt(pos.y());
	if (row != -1)
	{
		QAction *action = menu->exec(ui.Seginfo->mapToGlobal(pos));
		//printf("menu %d,%d" ,pos.x(), pos.y());
	}
	return;
}
void caffeui::SetModelFile()
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
void caffeui::SetProtoFile()
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
void caffeui::SetMeanFile()
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
void caffeui::SetOutputFile()
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
void caffeui::InitCaffe()
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
void caffeui::Caffed()
{
	ui.LogText->append("init caffe success");
}
void caffeui::getmes(int time, float score)
{
	char buf[100];
	sprintf(buf,"%2d:%2d -- %f", time / 60, time % 60, score);
	//printf(buf, "%2d:%2d -- %f", time / 60, time % 60, score);
	ui.LogText->append(buf);
	data.push_back(std::make_tuple(time, score));
}
void caffeui::AddSegitem(int stime, float score)
{
	segmentation *test = new segmentation(0,stime, score);
	_model->appendItem(test);

}
void caffeui::AnalysisMsg()
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
void caffeui::timerEvent(QTimerEvent * e)
{
	/*if (SplitVideo::Get()->bufsize > 0)
	{
		ui.LogText->setText(SplitVideo::Get()->getbuf());
	}*/
}
caffeui::~caffeui() {
	
}
