

#include <QtWidgets>
#include <QString>

#include "MainWindow.h"
#include "Qt5View.h"
#include "version.h"
#include "Qt5Version.h"

MainWindow::MainWindow(Qt5View *view, QWidget *parent) : QWidget(parent) {
    board = view;
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    QString version = QString("version:") + QString(VERSION_QT5) + QString("<br>model:") + QString(VERSION_MODEL);

    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(startButton, SIGNAL(clicked()), board, SLOT(restart()));
    connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board,                    0, 0, 5, 1, Qt::AlignCenter);

    layout->addWidget(createLabel(tr("SCORE")), 0, 1);
    layout->addWidget(scoreLcd,                 1, 1);
    layout->addWidget(startButton,              2, 1);
    layout->addWidget(quitButton,               3, 1);
    layout->addWidget(createLabel(version),     4, 1);
    setLayout(layout);

    setWindowTitle(tr("Snake"));
    resize(550, 370);
}

MainWindow::~MainWindow() {
    board->setParent(0);    //объект создан в стеке, а не в куче, удалять нельзя
}

QLabel *MainWindow::createLabel(const QString &text) {
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

