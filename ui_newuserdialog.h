/********************************************************************************
** Form generated from reading UI file 'newuserdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWUSERDIALOG_H
#define UI_NEWUSERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewUserDialog
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword1;
    QLabel *labelRetypePassword;
    QLineEdit *lineEditPassword2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButtonCreateUser;

    void setupUi(QDialog *NewUserDialog)
    {
        if (NewUserDialog->objectName().isEmpty())
            NewUserDialog->setObjectName(QStringLiteral("NewUserDialog"));
        NewUserDialog->resize(310, 176);
        layoutWidget = new QWidget(NewUserDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 30, 239, 118));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelUsername = new QLabel(layoutWidget);
        labelUsername->setObjectName(QStringLiteral("labelUsername"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelUsername);

        lineEditUsername = new QLineEdit(layoutWidget);
        lineEditUsername->setObjectName(QStringLiteral("lineEditUsername"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEditUsername);

        labelPassword = new QLabel(layoutWidget);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelPassword);

        lineEditPassword1 = new QLineEdit(layoutWidget);
        lineEditPassword1->setObjectName(QStringLiteral("lineEditPassword1"));

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEditPassword1);

        labelRetypePassword = new QLabel(layoutWidget);
        labelRetypePassword->setObjectName(QStringLiteral("labelRetypePassword"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelRetypePassword);

        lineEditPassword2 = new QLineEdit(layoutWidget);
        lineEditPassword2->setObjectName(QStringLiteral("lineEditPassword2"));

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEditPassword2);


        verticalLayout->addLayout(formLayout);


        verticalLayout_2->addLayout(verticalLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButtonCreateUser = new QPushButton(layoutWidget);
        pushButtonCreateUser->setObjectName(QStringLiteral("pushButtonCreateUser"));

        horizontalLayout->addWidget(pushButtonCreateUser);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(NewUserDialog);

        QMetaObject::connectSlotsByName(NewUserDialog);
    } // setupUi

    void retranslateUi(QDialog *NewUserDialog)
    {
        NewUserDialog->setWindowTitle(QApplication::translate("NewUserDialog", "Dialog", 0));
        labelUsername->setText(QApplication::translate("NewUserDialog", "Username", 0));
        labelPassword->setText(QApplication::translate("NewUserDialog", "Password", 0));
        labelRetypePassword->setText(QApplication::translate("NewUserDialog", "Retype Password", 0));
        pushButtonCreateUser->setText(QApplication::translate("NewUserDialog", "Create new User", 0));
    } // retranslateUi

};

namespace Ui {
    class NewUserDialog: public Ui_NewUserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWUSERDIALOG_H
