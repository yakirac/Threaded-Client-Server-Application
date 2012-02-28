/********************************************************************************
** Form generated from reading UI file 'tcst.ui'
**
** Created: Thu Dec 9 19:14:36 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TCST_H
#define UI_TCST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TCSTClass
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *userLabel;
    QLineEdit *userLineEdit;
    QLabel *passLabel;
    QLineEdit *passLineEdit;
    QLabel *statusLabel;
    QComboBox *comboBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *registerButton;
    QPushButton *loginButton;
    QPushButton *cancelButton;
    QPushButton *button1;
    QPushButton *button2;
    QListWidget *resultList;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QDialog *TCSTClass)
    {
        if (TCSTClass->objectName().isEmpty())
            TCSTClass->setObjectName(QString::fromUtf8("TCSTClass"));
        TCSTClass->resize(400, 300);
        widget = new QWidget(TCSTClass);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 80, 331, 151));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        userLabel = new QLabel(widget);
        userLabel->setObjectName(QString::fromUtf8("userLabel"));

        verticalLayout->addWidget(userLabel);

        userLineEdit = new QLineEdit(widget);
        userLineEdit->setObjectName(QString::fromUtf8("userLineEdit"));

        verticalLayout->addWidget(userLineEdit);

        passLabel = new QLabel(widget);
        passLabel->setObjectName(QString::fromUtf8("passLabel"));

        verticalLayout->addWidget(passLabel);

        passLineEdit = new QLineEdit(widget);
        passLineEdit->setObjectName(QString::fromUtf8("passLineEdit"));

        verticalLayout->addWidget(passLineEdit);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        registerButton = new QPushButton(widget);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));

        horizontalLayout->addWidget(registerButton);

        loginButton = new QPushButton(widget);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        horizontalLayout->addWidget(loginButton);

        cancelButton = new QPushButton(widget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);


        retranslateUi(TCSTClass);

        QMetaObject::connectSlotsByName(TCSTClass);
    } // setupUi

    void retranslateUi(QDialog *TCSTClass)
    {
        TCSTClass->setWindowTitle(QApplication::translate("TCSTClass", "TCST", 0, QApplication::UnicodeUTF8));
        userLabel->setText(QApplication::translate("TCSTClass", "Username:", 0, QApplication::UnicodeUTF8));
        passLabel->setText(QApplication::translate("TCSTClass", "Password:", 0, QApplication::UnicodeUTF8));
        registerButton->setText(QApplication::translate("TCSTClass", "Register", 0, QApplication::UnicodeUTF8));
        loginButton->setText(QApplication::translate("TCSTClass", "Login", 0, QApplication::UnicodeUTF8));
        cancelButton->setText(QApplication::translate("TCSTClass", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TCSTClass: public Ui_TCSTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TCST_H
