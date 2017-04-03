/********************************************************************************
** Form generated from reading UI file 'caffeui.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAFFEUI_H
#define UI_CAFFEUI_H

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

QT_BEGIN_NAMESPACE

class Ui_caffeui
{
public:
    QLineEdit *ModelEdit;
    QLineEdit *ProtoEdit;
    QLineEdit *MeanEdit;
    QPushButton *ModelButton;
    QPushButton *ProtoButton;
    QPushButton *MeanButton;
    QTableView *Seginfo;
    QTextEdit *LogText;
    QLineEdit *OutputDirEdit;
    QPushButton *OutputDir;
    QPushButton *InitCaffe;
    QPushButton *AnalysisBt;
    QLineEdit *ScoreIp;
    QLabel *ScoreLb;

    void setupUi(QWidget *caffeui)
    {
        if (caffeui->objectName().isEmpty())
            caffeui->setObjectName(QStringLiteral("caffeui"));
        caffeui->resize(554, 866);
        ModelEdit = new QLineEdit(caffeui);
        ModelEdit->setObjectName(QStringLiteral("ModelEdit"));
        ModelEdit->setGeometry(QRect(10, 10, 401, 21));
        ProtoEdit = new QLineEdit(caffeui);
        ProtoEdit->setObjectName(QStringLiteral("ProtoEdit"));
        ProtoEdit->setGeometry(QRect(10, 40, 401, 21));
        MeanEdit = new QLineEdit(caffeui);
        MeanEdit->setObjectName(QStringLiteral("MeanEdit"));
        MeanEdit->setGeometry(QRect(10, 70, 401, 21));
        ModelButton = new QPushButton(caffeui);
        ModelButton->setObjectName(QStringLiteral("ModelButton"));
        ModelButton->setGeometry(QRect(440, 10, 81, 21));
        ProtoButton = new QPushButton(caffeui);
        ProtoButton->setObjectName(QStringLiteral("ProtoButton"));
        ProtoButton->setGeometry(QRect(440, 40, 81, 21));
        MeanButton = new QPushButton(caffeui);
        MeanButton->setObjectName(QStringLiteral("MeanButton"));
        MeanButton->setGeometry(QRect(440, 70, 81, 21));
        Seginfo = new QTableView(caffeui);
        Seginfo->setObjectName(QStringLiteral("Seginfo"));
        Seginfo->setGeometry(QRect(10, 410, 531, 451));
        LogText = new QTextEdit(caffeui);
        LogText->setObjectName(QStringLiteral("LogText"));
        LogText->setGeometry(QRect(10, 220, 531, 181));
        OutputDirEdit = new QLineEdit(caffeui);
        OutputDirEdit->setObjectName(QStringLiteral("OutputDirEdit"));
        OutputDirEdit->setGeometry(QRect(10, 100, 401, 21));
        OutputDir = new QPushButton(caffeui);
        OutputDir->setObjectName(QStringLiteral("OutputDir"));
        OutputDir->setGeometry(QRect(440, 100, 81, 21));
        InitCaffe = new QPushButton(caffeui);
        InitCaffe->setObjectName(QStringLiteral("InitCaffe"));
        InitCaffe->setGeometry(QRect(20, 130, 71, 31));
        AnalysisBt = new QPushButton(caffeui);
        AnalysisBt->setObjectName(QStringLiteral("AnalysisBt"));
        AnalysisBt->setGeometry(QRect(440, 130, 71, 31));
        ScoreIp = new QLineEdit(caffeui);
        ScoreIp->setObjectName(QStringLiteral("ScoreIp"));
        ScoreIp->setGeometry(QRect(360, 130, 51, 21));
        ScoreLb = new QLabel(caffeui);
        ScoreLb->setObjectName(QStringLiteral("ScoreLb"));
        ScoreLb->setGeometry(QRect(320, 130, 41, 21));

        retranslateUi(caffeui);
        QObject::connect(ModelButton, SIGNAL(clicked()), caffeui, SLOT(SetModelFile()));
        QObject::connect(ProtoButton, SIGNAL(clicked()), caffeui, SLOT(SetProtoFile()));
        QObject::connect(MeanButton, SIGNAL(clicked()), caffeui, SLOT(SetMeanFile()));
        QObject::connect(OutputDir, SIGNAL(clicked()), caffeui, SLOT(SetOutputFile()));

        QMetaObject::connectSlotsByName(caffeui);
    } // setupUi

    void retranslateUi(QWidget *caffeui)
    {
        caffeui->setWindowTitle(QApplication::translate("caffeui", "caffeui", Q_NULLPTR));
        ModelButton->setText(QApplication::translate("caffeui", "Model\346\226\207\344\273\266", Q_NULLPTR));
        ProtoButton->setText(QApplication::translate("caffeui", "Proto\346\226\207\344\273\266", Q_NULLPTR));
        MeanButton->setText(QApplication::translate("caffeui", "Mean\346\226\207\344\273\266", Q_NULLPTR));
        OutputDir->setText(QApplication::translate("caffeui", "\345\255\230\346\224\276\344\275\215\347\275\256", Q_NULLPTR));
        InitCaffe->setText(QApplication::translate("caffeui", "InitCaffe", Q_NULLPTR));
        AnalysisBt->setText(QApplication::translate("caffeui", "Analysis", Q_NULLPTR));
        ScoreLb->setText(QApplication::translate("caffeui", "score>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class caffeui: public Ui_caffeui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAFFEUI_H
