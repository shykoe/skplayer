#pragma once
#include <qslider.h>
class sSlider: public QSlider
{
	Q_OBJECT
public:
	sSlider(QWidget *p = NULL);
	virtual ~sSlider();
	void mousePressEvent(QMouseEvent *e);
};

