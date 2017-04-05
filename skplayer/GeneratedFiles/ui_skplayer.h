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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
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
    QLineEdit *ModelEdit;
    QLabel *ScoreLb;
    QLineEdit *MeanEdit;
    QPushButton *ModelButton;
    QPushButton *AnalysisBt;
    QLineEdit *ScoreIp;
    QLineEdit *ProtoEdit;
    QPushButton *OutputDir;
    QPushButton *InitCaffe;
    QPushButton *ProtoButton;
    QLineEdit *OutputDirEdit;
    QPushButton *MeanButton;
    QTableView *Seginfo;
    QTextEdit *LogText;
    QPushButton *SplitBt;
    QLineEdit *StartTm;
    QLineEdit *EndTm;
    QLabel *ScoreLb_2;
    QLabel *ScoreLb_3;
    QPushButton *ResetSE;
    QLineEdit *FileName;
    QLabel *ScoreLb_4;
    QLabel *suffixName;

    void setupUi(QWidget *skplayerClass)
    {
        if (skplayerClass->objectName().isEmpty())
            skplayerClass->setObjectName(QStringLiteral("skplayerClass"));
        skplayerClass->resize(1125, 896);
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
        ModelEdit = new QLineEdit(skplayerClass);
        ModelEdit->setObjectName(QStringLiteral("ModelEdit"));
        ModelEdit->setGeometry(QRect(80, 670, 401, 21));
        ScoreLb = new QLabel(skplayerClass);
        ScoreLb->setObjectName(QStringLiteral("ScoreLb"));
        ScoreLb->setGeometry(QRect(390, 790, 41, 21));
        MeanEdit = new QLineEdit(skplayerClass);
        MeanEdit->setObjectName(QStringLiteral("MeanEdit"));
        MeanEdit->setGeometry(QRect(80, 730, 401, 21));
        ModelButton = new QPushButton(skplayerClass);
        ModelButton->setObjectName(QStringLiteral("ModelButton"));
        ModelButton->setGeometry(QRect(510, 670, 81, 21));
        AnalysisBt = new QPushButton(skplayerClass);
        AnalysisBt->setObjectName(QStringLiteral("AnalysisBt"));
        AnalysisBt->setGeometry(QRect(510, 790, 71, 31));
        ScoreIp = new QLineEdit(skplayerClass);
        ScoreIp->setObjectName(QStringLiteral("ScoreIp"));
        ScoreIp->setGeometry(QRect(430, 790, 51, 21));
        ProtoEdit = new QLineEdit(skplayerClass);
        ProtoEdit->setObjectName(QStringLiteral("ProtoEdit"));
        ProtoEdit->setGeometry(QRect(80, 700, 401, 21));
        OutputDir = new QPushButton(skplayerClass);
        OutputDir->setObjectName(QStringLiteral("OutputDir"));
        OutputDir->setGeometry(QRect(510, 760, 81, 21));
        InitCaffe = new QPushButton(skplayerClass);
        InitCaffe->setObjectName(QStringLiteral("InitCaffe"));
        InitCaffe->setGeometry(QRect(90, 790, 71, 31));
        ProtoButton = new QPushButton(skplayerClass);
        ProtoButton->setObjectName(QStringLiteral("ProtoButton"));
        ProtoButton->setGeometry(QRect(510, 700, 81, 21));
        OutputDirEdit = new QLineEdit(skplayerClass);
        OutputDirEdit->setObjectName(QStringLiteral("OutputDirEdit"));
        OutputDirEdit->setGeometry(QRect(80, 760, 401, 21));
        MeanButton = new QPushButton(skplayerClass);
        MeanButton->setObjectName(QStringLiteral("MeanButton"));
        MeanButton->setGeometry(QRect(510, 730, 81, 21));
        Seginfo = new QTableView(skplayerClass);
        Seginfo->setObjectName(QStringLiteral("Seginfo"));
        Seginfo->setGeometry(QRect(800, 0, 321, 601));
        LogText = new QTextEdit(skplayerClass);
        LogText->setObjectName(QStringLiteral("LogText"));
        LogText->setGeometry(QRect(590, 600, 531, 291));
        SplitBt = new QPushButton(skplayerClass);
        SplitBt->setObjectName(QStringLiteral("SplitBt"));
        SplitBt->setGeometry(QRect(90, 830, 71, 31));
        StartTm = new QLineEdit(skplayerClass);
        StartTm->setObjectName(QStringLiteral("StartTm"));
        StartTm->setGeometry(QRect(220, 840, 51, 21));
        EndTm = new QLineEdit(skplayerClass);
        EndTm->setObjectName(QStringLiteral("EndTm"));
        EndTm->setGeometry(QRect(320, 840, 51, 21));
        ScoreLb_2 = new QLabel(skplayerClass);
        ScoreLb_2->setObjectName(QStringLiteral("ScoreLb_2"));
        ScoreLb_2->setGeometry(QRect(180, 840, 41, 21));
        ScoreLb_3 = new QLabel(skplayerClass);
        ScoreLb_3->setObjectName(QStringLiteral("ScoreLb_3"));
        ScoreLb_3->setGeometry(QRect(290, 840, 41, 21));
        ResetSE = new QPushButton(skplayerClass);
        ResetSE->setObjectName(QStringLiteral("ResetSE"));
        ResetSE->setGeometry(QRect(400, 840, 81, 21));
        FileName = new QLineEdit(skplayerClass);
        FileName->setObjectName(QStringLiteral("FileName"));
        FileName->setGeometry(QRect(230, 870, 91, 21));
        ScoreLb_4 = new QLabel(skplayerClass);
        ScoreLb_4->setObjectName(QStringLiteral("ScoreLb_4"));
        ScoreLb_4->setGeometry(QRect(180, 870, 51, 21));
        suffixName = new QLabel(skplayerClass);
        suffixName->setObjectName(QStringLiteral("suffixName"));
        suffixName->setGeometry(QRect(330, 870, 51, 21));

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
        ScoreLb->setText(QApplication::translate("skplayerClass", "score>", Q_NULLPTR));
        ModelButton->setText(QApplication::translate("skplayerClass", "Model\346\226\207\344\273\266", Q_NULLPTR));
        AnalysisBt->setText(QApplication::translate("skplayerClass", "Analysis", Q_NULLPTR));
        OutputDir->setText(QApplication::translate("skplayerClass", "\345\255\230\346\224\276\344\275\215\347\275\256", Q_NULLPTR));
        InitCaffe->setText(QApplication::translate("skplayerClass", "InitCaffe", Q_NULLPTR));
        ProtoButton->setText(QApplication::translate("skplayerClass", "Proto\346\226\207\344\273\266", Q_NULLPTR));
        MeanButton->setText(QApplication::translate("skplayerClass", "Mean\346\226\207\344\273\266", Q_NULLPTR));
        SplitBt->setText(QApplication::translate("skplayerClass", "\345\210\206\345\211\262\350\247\206\351\242\221", Q_NULLPTR));
        ScoreLb_2->setText(QApplication::translate("skplayerClass", "Start", Q_NULLPTR));
        ScoreLb_3->setText(QApplication::translate("skplayerClass", "End", Q_NULLPTR));
        ResetSE->setText(QApplication::translate("skplayerClass", "\344\275\277\347\224\250\350\276\223\345\205\245\346\227\266\351\227\264", Q_NULLPTR));
        ScoreLb_4->setText(QApplication::translate("skplayerClass", "\346\226\207\344\273\266\345\220\215\347\247\260", Q_NULLPTR));
        suffixName->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class skplayerClass: public Ui_skplayerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SKPLAYER_H
