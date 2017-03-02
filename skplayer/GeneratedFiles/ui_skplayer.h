/********************************************************************************
** Form generated from reading UI file 'skplayer.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SKPLAYER_H
#define UI_SKPLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "sslider.h"
#include "videowidget.h"

QT_BEGIN_NAMESPACE

class Ui_skplayerClass
{
public:
    VideoWidget *openGLWidget;
    QPushButton *openButton;
    QPushButton *playButton;
    QLabel *playTime1;
    QLabel *playTime1_2;
    QLabel *sp;
    sSlider *playslider;

    void setupUi(QWidget *skplayerClass)
    {
        if (skplayerClass->objectName().isEmpty())
            skplayerClass->setObjectName(QStringLiteral("skplayerClass"));
        skplayerClass->resize(800, 600);
        QIcon icon;
        icon.addFile(QStringLiteral(":/skplayer/Resources/play_128px_1194928_easyicon.net.ico"), QSize(), QIcon::Normal, QIcon::Off);
        skplayerClass->setWindowIcon(icon);
        openGLWidget = new VideoWidget(skplayerClass);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(0, 0, 800, 600));
        openButton = new QPushButton(skplayerClass);
        openButton->setObjectName(QStringLiteral("openButton"));
        openButton->setGeometry(QRect(30, 530, 61, 41));
        openButton->setStyleSheet(QStringLiteral("border-image:url(:/skplayer/Resources/Folder_open_246px_1198271_easyicon.net.png)"));
        playButton = new QPushButton(skplayerClass);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(90, 530, 61, 41));
        playButton->setStyleSheet(QStringLiteral("QPushButton{border-image: url(:/skplayer/Resources/play_703px_1194928_easyicon.net.png);}"));
        playTime1 = new QLabel(skplayerClass);
        playTime1->setObjectName(QStringLiteral("playTime1"));
        playTime1->setGeometry(QRect(200, 540, 41, 21));
        playTime1->setStyleSheet(QString::fromUtf8("color: rgb(242, 255, 228);\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        playTime1_2 = new QLabel(skplayerClass);
        playTime1_2->setObjectName(QStringLiteral("playTime1_2"));
        playTime1_2->setGeometry(QRect(150, 540, 41, 21));
        playTime1_2->setStyleSheet(QString::fromUtf8("color: rgb(242, 255, 228);\n"
"font: 9pt \"\351\273\221\344\275\223\";"));
        sp = new QLabel(skplayerClass);
        sp->setObjectName(QStringLiteral("sp"));
        sp->setGeometry(QRect(190, 540, 16, 21));
        sp->setStyleSheet(QStringLiteral("color: rgb(234, 255, 242);"));
        playslider = new sSlider(skplayerClass);
        playslider->setObjectName(QStringLiteral("playslider"));
        playslider->setGeometry(QRect(240, 540, 551, 21));
        playslider->setMaximum(999);
        playslider->setOrientation(Qt::Horizontal);

        retranslateUi(skplayerClass);
        QObject::connect(openButton, SIGNAL(clicked()), skplayerClass, SLOT(open()));
        QObject::connect(playslider, SIGNAL(sliderReleased()), skplayerClass, SLOT(sliderReleased()));
        QObject::connect(playslider, SIGNAL(sliderPressed()), skplayerClass, SLOT(sliderPressed()));
        QObject::connect(playButton, SIGNAL(clicked()), skplayerClass, SLOT(play()));

        QMetaObject::connectSlotsByName(skplayerClass);
    } // setupUi

    void retranslateUi(QWidget *skplayerClass)
    {
        skplayerClass->setWindowTitle(QApplication::translate("skplayerClass", "skplayer", Q_NULLPTR));
        openButton->setText(QString());
        playButton->setText(QString());
        playTime1->setText(QApplication::translate("skplayerClass", "000:00", Q_NULLPTR));
        playTime1_2->setText(QApplication::translate("skplayerClass", "000:00", Q_NULLPTR));
        sp->setText(QApplication::translate("skplayerClass", "/", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class skplayerClass: public Ui_skplayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKPLAYER_H
