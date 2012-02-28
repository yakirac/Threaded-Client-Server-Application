/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created: Thu Dec 9 22:13:11 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialogClass
{
public:
    QPushButton *okButton;
    QPushButton *cancelButton;
    QLabel *nameLabel;
    QLabel *passLabel;
    QLineEdit *nameEdit;
    QLineEdit *passEdit;
    QLabel *statusLabel;

    void setupUi(QDialog *RegisterDialogClass)
    {
        if (RegisterDialogClass->objectName().isEmpty())
            RegisterDialogClass->setObjectName(QString::fromUtf8("RegisterDialogClass"));
        RegisterDialogClass->resize(341, 206);
        okButton = new QPushButton(RegisterDialogClass);
        okButton->setObjectName(QString::fromUtf8("registerButton"));
        okButton->setGeometry(QRect(120, 170, 75, 23));
        cancelButton = new QPushButton(RegisterDialogClass);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        cancelButton->setGeometry(QRect(210, 170, 75, 23));
        nameLabel = new QLabel(RegisterDialogClass);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        nameLabel->setGeometry(QRect(50, 10, 81, 16));
        passLabel = new QLabel(RegisterDialogClass);
        passLabel->setObjectName(QString::fromUtf8("passLabel"));
        passLabel->setGeometry(QRect(50, 60, 81, 16));
        nameEdit = new QLineEdit(RegisterDialogClass);
        nameEdit->setObjectName(QString::fromUtf8("nameEdit"));
        nameEdit->setGeometry(QRect(50, 30, 231, 20));
        passEdit = new QLineEdit(RegisterDialogClass);
        passEdit->setObjectName(QString::fromUtf8("passEdit"));
        passEdit->setGeometry(QRect(50, 80, 231, 20));
        statusLabel = new QLabel(RegisterDialogClass);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(30, 110, 281, 41));

        retranslateUi(RegisterDialogClass);

        QMetaObject::connectSlotsByName(RegisterDialogClass);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialogClass)
    {
        RegisterDialogClass->setWindowTitle(QApplication::translate("RegisterDialogClass", "Register", 0, QApplication::UnicodeUTF8));
        okButton->setText(QApplication::translate("RegisterDialogClass", "Register", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("RegisterDialogClass", "Cancel", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QApplication::translate("RegisterDialogClass", "New Username:", 0, QApplication::UnicodeUTF8));
        passLabel->setText(QApplication::translate("RegisterDialogClass", "New Password:", 0, QApplication::UnicodeUTF8));
        statusLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RegisterDialogClass: public Ui_RegisterDialogClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
