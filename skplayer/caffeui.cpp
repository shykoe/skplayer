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
	ui.Seginfo->setModel(_model);
	ui.Seginfo->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.Seginfo->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.LogText->setReadOnly(true);
	connect(ui.Seginfo, SIGNAL(customContextMenuRequested(const QPoint)), this, SLOT(contextMenu(const QPoint)));
	segmentation *test = new segmentation(1, 11, 2, 33, tr("test.mp4"));
	segmentation *test2 = new segmentation(1, 11, 2, 33, tr("test.mp4"));
	segmentation *test3 = new segmentation(1, 11, 2, 33, tr("test.mp4"));
	_model->appendItem(test);
	_model->appendItem(test2);
	_model->appendItem(test3);
	startTimer(40);
	
}
void caffeui::contextMenu(const QPoint &pos)
{
	int row = ui.Seginfo->rowAt(pos.y());
	if (row != -1)
	{
		QMenu menu;
		QAction *openAction = menu.addAction(QString::fromLocal8Bit("分割视频"));
		QAction *action = menu.exec(ui.Seginfo->mapToGlobal(pos));
		//printf("menu %d,%d" ,pos.x(), pos.y());
	}
	return;
}
void caffeui::SetModelFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择caffemodel文件"));
	printf("%s", name.toStdString().c_str());
	ui.ModelEdit->setText(name);
}
void caffeui::SetProtoFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择proto文件"));
	printf("%s", name.toStdString().c_str());
	ui.ProtoEdit->setText(name);
}
void caffeui::SetMeanFile()
{
	QString name = QFileDialog::getOpenFileName(
		this, QString::fromLocal8Bit("选择mean文件"));
	printf("%s", name.toStdString().c_str());
	ui.MeanEdit->setText(name);
}
void caffeui::SetOutputFile()
{
	QString name = QFileDialog::getExistingDirectory(
		this, QString::fromLocal8Bit("选择存放位置")
	);
	printf("%s", name.toStdString().c_str());
	ui.OutputDirEdit->setText(name);
}
void caffeui::timerEvent(QTimerEvent * e)
{
	if (SplitVideo::Get()->bufsize > 0)
	{
		ui.LogText->setText(SplitVideo::Get()->getbuf());
	}
}
caffeui::~caffeui() {
	
}
