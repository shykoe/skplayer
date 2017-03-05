#pragma once
#include <QWidget>
#include "ui_caffeui.h"

class caffeui : public QWidget {
	Q_OBJECT

public:
	caffeui(QWidget * parent = Q_NULLPTR);
	~caffeui();
public slots:
	void SetModelFile();
	void SetMeanFile();
	void SetProtoFile();
private:
	Ui::caffeui ui;
};
