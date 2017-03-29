#include "caffeui.hpp"
#include "qfiledialog.h"
#include "qstring.h"
#include "qtableview.h"
#include "SplitVideo.h"
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
	ui.Seginfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.Seginfo->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.LogText->setReadOnly(true);
	ui.OutputDirEdit->setText(QCoreApplication::applicationDirPath());
	menu = new QMenu();
	QAction *splitAction = menu->addAction(QString::fromLocal8Bit("分割视频"));

	mythread = new CaffeThread(this);
	string model_file = "E:\\videocaffedata\\template_net.prototxt";
	string trained_file = "E:\\videocaffedata\\_iter_15000.caffemodel";
	string mean_file = "E:\\videocaffedata\\seg_leveldb_mean";
	string label_file = "synset_words.txt";

	mythread->SetConf(model_file, trained_file, mean_file);

	connect(this->mythread, SIGNAL(CaffeInit()), this, SLOT(Caffed()));
	connect(ui.Seginfo, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(contextMenu(const QPoint)));
	connect(splitAction, &QAction::triggered, this, &caffeui::splitvideo);
	connect(ui.InitCaffe, SIGNAL(clicked()), SLOT(InitCaffe()));
	


	//debug
	segmentation *test = new segmentation(1, 11, 2, 33, tr("test.mp4"));
	segmentation *test2 = new segmentation(1, 11, 2, 33, tr("test.mp4"));
	segmentation *test3 = new segmentation(1, 11, 2, 33, tr("test.mp4"));
	_model->appendItem(test);
	_model->appendItem(test2);
	_model->appendItem(test3);
	SplitVideo::Get()->OpenSource("D:\\BaiduYunDownload\\Ariana Grande - Into You.mp4");


	startTimer(40);
	
}
void caffeui::splitvideo()
{
	printf("%d\n", ui.Seginfo->currentIndex().row());
	auto start = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(1);
	auto end = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(2);
	auto dur = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(3);
	auto name = _model->getItem(ui.Seginfo->currentIndex().row())->truedata(4);
	printf("%s\n", SplitVideo::Get()->getpath().c_str());
	printf("%d-%d-%d-%s\n", start.toInt(), end.toInt(), dur.toInt(),name.toString().toStdString().c_str());
	if (SplitVideo::Get()->isopen)
	{
		SplitVideo::Get()->Split(start.toInt(), dur.toInt(), ui.OutputDirEdit->text().toStdString() + "//"+name.toString().toStdString());
	}
	
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
	ui.InitCaffe->setEnabled(false);
	this->mythread->run();
}
void caffeui::Caffed()
{
	ui.InitCaffe->setEnabled(true);
	ui.LogText->append("init caffe success");
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
