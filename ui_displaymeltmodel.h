/********************************************************************************
** Form generated from reading UI file 'displaymeltmodel.ui'
**
** Created by: Qt User Interface Compiler version 5.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAYMELTMODEL_H
#define UI_DISPLAYMELTMODEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_displaymeltmodel
{
public:
    QAction *open;
    QAction *save;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTableView *view;
    QHBoxLayout *horizontalLayout;
    QLineEdit *x;
    QLineEdit *y;
    QLineEdit *startTemp;
    QPushButton *start;
    QPushButton *step;
    QMenuBar *menuBar;
    QMenu *menu;

    void setupUi(QMainWindow *displaymeltmodel)
    {
        if (displaymeltmodel->objectName().isEmpty())
            displaymeltmodel->setObjectName(QStringLiteral("displaymeltmodel"));
        displaymeltmodel->resize(443, 417);
        open = new QAction(displaymeltmodel);
        open->setObjectName(QStringLiteral("open"));
        save = new QAction(displaymeltmodel);
        save->setObjectName(QStringLiteral("save"));
        centralWidget = new QWidget(displaymeltmodel);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        view = new QTableView(centralWidget);
        view->setObjectName(QStringLiteral("view"));

        verticalLayout->addWidget(view);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        x = new QLineEdit(centralWidget);
        x->setObjectName(QStringLiteral("x"));

        horizontalLayout->addWidget(x);

        y = new QLineEdit(centralWidget);
        y->setObjectName(QStringLiteral("y"));

        horizontalLayout->addWidget(y);

        startTemp = new QLineEdit(centralWidget);
        startTemp->setObjectName(QStringLiteral("startTemp"));

        horizontalLayout->addWidget(startTemp);

        start = new QPushButton(centralWidget);
        start->setObjectName(QStringLiteral("start"));

        horizontalLayout->addWidget(start);


        verticalLayout->addLayout(horizontalLayout);

        step = new QPushButton(centralWidget);
        step->setObjectName(QStringLiteral("step"));

        verticalLayout->addWidget(step);

        displaymeltmodel->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(displaymeltmodel);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 443, 18));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        displaymeltmodel->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(open);
        menu->addAction(save);

        retranslateUi(displaymeltmodel);

        QMetaObject::connectSlotsByName(displaymeltmodel);
    } // setupUi

    void retranslateUi(QMainWindow *displaymeltmodel)
    {
        displaymeltmodel->setWindowTitle(QApplication::translate("displaymeltmodel", "meltmodel", 0));
        open->setText(QApplication::translate("displaymeltmodel", "\320\276\321\202\320\272\321\200\321\213\321\202\321\214", 0));
        open->setShortcut(QApplication::translate("displaymeltmodel", "Ctrl+O", 0));
        save->setText(QApplication::translate("displaymeltmodel", "\321\201\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        save->setShortcut(QApplication::translate("displaymeltmodel", "Ctrl+S", 0));
        x->setText(QApplication::translate("displaymeltmodel", "5", 0));
        y->setText(QApplication::translate("displaymeltmodel", "5", 0));
        startTemp->setText(QApplication::translate("displaymeltmodel", "0", 0));
        start->setText(QApplication::translate("displaymeltmodel", "\320\235\320\260\321\207\320\260\321\202\321\214", 0));
        step->setText(QApplication::translate("displaymeltmodel", "\320\250\320\260\320\263", 0));
        menu->setTitle(QApplication::translate("displaymeltmodel", "\320\244\320\260\320\271\320\273", 0));
    } // retranslateUi

};

namespace Ui {
    class displaymeltmodel: public Ui_displaymeltmodel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAYMELTMODEL_H
