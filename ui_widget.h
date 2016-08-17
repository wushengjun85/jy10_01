/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created: Wed Aug 17 17:39:55 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *ptn_back;
    QPushButton *pushButton_timesetup;
    QLCDNumber *lcdNumber;
    QPushButton *pushButton_timesetup_2;
    QPushButton *pushButton_timesetup_3;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLCDNumber *lcdNumber_2;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(1024, 600);
        ptn_back = new QPushButton(Widget);
        ptn_back->setObjectName(QString::fromUtf8("ptn_back"));
        ptn_back->setGeometry(QRect(760, 550, 45, 33));
        ptn_back->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/imagejy/qihuan.png);"));
        pushButton_timesetup = new QPushButton(Widget);
        pushButton_timesetup->setObjectName(QString::fromUtf8("pushButton_timesetup"));
        pushButton_timesetup->setGeometry(QRect(860, 550, 41, 41));
        pushButton_timesetup->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/imagejy/setup.png);"));
        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setGeometry(QRect(530, 470, 251, 61));
        lcdNumber->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber->setFrameShape(QFrame::NoFrame);
        lcdNumber->setDigitCount(8);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);
        pushButton_timesetup_2 = new QPushButton(Widget);
        pushButton_timesetup_2->setObjectName(QString::fromUtf8("pushButton_timesetup_2"));
        pushButton_timesetup_2->setGeometry(QRect(680, 550, 37, 39));
        pushButton_timesetup_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/imagejy/find.png);"));
        pushButton_timesetup_3 = new QPushButton(Widget);
        pushButton_timesetup_3->setObjectName(QString::fromUtf8("pushButton_timesetup_3"));
        pushButton_timesetup_3->setGeometry(QRect(900, 480, 39, 37));
        pushButton_timesetup_3->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/imagejy/laba.png);"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(473, 226, 104, 42));
        label->setStyleSheet(QString::fromUtf8("font: 22pt \"Ubuntu\";"));
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(473, 269, 104, 42));
        label_2->setStyleSheet(QString::fromUtf8("font: 22pt \"Ubuntu\";"));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(473, 313, 104, 42));
        label_3->setStyleSheet(QString::fromUtf8("font: 22pt \"Ubuntu\";"));
        label_4 = new QLabel(Widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(473, 357, 104, 42));
        label_4->setStyleSheet(QString::fromUtf8("font: 22pt \"Ubuntu\";"));
        label_5 = new QLabel(Widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(446, 399, 162, 45));
        label_5->setStyleSheet(QString::fromUtf8("font: 22pt \"Ubuntu\";"));
        label_6 = new QLabel(Widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(320, 540, 351, 51));
        lcdNumber_2 = new QLCDNumber(Widget);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setGeometry(QRect(220, 470, 331, 61));
        lcdNumber_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lcdNumber_2->setFrameShape(QFrame::NoFrame);
        lcdNumber_2->setDigitCount(10);
        lcdNumber_2->setSegmentStyle(QLCDNumber::Filled);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0, QApplication::UnicodeUTF8));
        ptn_back->setText(QString());
        pushButton_timesetup->setText(QString());
        pushButton_timesetup_2->setText(QString());
        pushButton_timesetup_3->setText(QString());
        label->setText(QString());
        label_2->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:20pt;\"><br/></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("Widget", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("Widget", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("Widget", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("Widget", "<html><head/><body><p><span style=\" font-size:22pt; color:#ff0000;\">\350\261\252\345\250\201\345\260\224\350\261\252\345\250\201\345\260\224\350\261\252\345\250\201\345\260\224\350\261\252\345\250\201\345\260\224</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
