#include "caffeui.hpp"
#include "qfiledialog.h"
#include "qstring.h"
caffeui::caffeui(QWidget * parent) : QWidget(parent) {
	ui.setupUi(this);
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
caffeui::~caffeui() {
	
}
