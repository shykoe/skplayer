#include "sSlider.h"
#include <QMouseEvent>


sSlider::sSlider(QWidget *p):QSlider(p)
{

}


sSlider::~sSlider()
{
}

void sSlider::mousePressEvent(QMouseEvent *e)
{
	int value = (e->pos().x() * this->maximum()) / this->width() + 1;
	this->setValue(value);
	QSlider::mousePressEvent(e);
}

