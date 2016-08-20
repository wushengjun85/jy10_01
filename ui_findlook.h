/********************************************************************************
** Form generated from reading UI file 'findlook.ui'
**
** Created: Sat Aug 20 08:54:42 2016
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDLOOK_H
#define UI_FINDLOOK_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FindLook
{
public:
    QPushButton *pushButton;

    void setupUi(QDialog *FindLook)
    {
        if (FindLook->objectName().isEmpty())
            FindLook->setObjectName(QString::fromUtf8("FindLook"));
        FindLook->resize(1024, 600);
        pushButton = new QPushButton(FindLook);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(950, 550, 51, 32));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/imagejy/back.png);"));

        retranslateUi(FindLook);

        QMetaObject::connectSlotsByName(FindLook);
    } // setupUi

    void retranslateUi(QDialog *FindLook)
    {
        FindLook->setWindowTitle(QApplication::translate("FindLook", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FindLook: public Ui_FindLook {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDLOOK_H
