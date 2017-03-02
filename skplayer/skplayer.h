#ifndef SKPLAYER_H
#define SKPLAYER_H

#include <QtWidgets/QWidget>
#include "ui_skplayer.h"

class skplayer : public QWidget
{
	Q_OBJECT

public:
	skplayer(QWidget *parent = 0);
	~skplayer();
	void timerEvent(QTimerEvent *e);
	void resizeEvent(QResizeEvent *e);
	void openFile(QString filename);
public slots:
	void open();
	void sliderPressed();
	void sliderReleased();
	void play();
private:
	int VideoWidth = 0;
	int VideoHeight = 0;
	
	Ui::skplayerClass ui;
};

#endif // SKPLAYER_H
