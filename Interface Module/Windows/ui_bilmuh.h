/********************************************************************************
** Form generated from reading UI file 'bilmuh.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BILMUH_H
#define UI_BILMUH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_BilMuh
{
public:

    void setupUi(QDialog *BilMuh)
    {
        if (BilMuh->objectName().isEmpty())
            BilMuh->setObjectName(QStringLiteral("BilMuh"));
        BilMuh->resize(820, 760);

        retranslateUi(BilMuh);

        QMetaObject::connectSlotsByName(BilMuh);
    } // setupUi

    void retranslateUi(QDialog *BilMuh)
    {
        BilMuh->setWindowTitle(QApplication::translate("BilMuh", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class BilMuh: public Ui_BilMuh {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BILMUH_H
