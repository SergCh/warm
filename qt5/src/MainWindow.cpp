

#include <QtWidgets>

#include "MainWindow.h"
#include "Qt5View.h"
#include "Qt5Board.h"
#include "version.h"

MainWindow::MainWindow(Qt5View *view, QWidget *parent) : QWidget(parent) {
    board = new Qt5Board(view);
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(startButton, SIGNAL(clicked()), board, SLOT(restart()));
    connect(board, SIGNAL(scoreChanged(int)), scoreLcd, SLOT(display(int)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board,                    0, 0, 5, 1, Qt::AlignCenter);

    layout->addWidget(createLabel(tr("SCORE")), 0, 1);
    layout->addWidget(scoreLcd,                 1, 1);
    layout->addWidget(startButton,              2, 1);
    layout->addWidget(quitButton,               3, 1);
    layout->addWidget(createLabel(tr(VERSION)), 4, 1);
    setLayout(layout);

    setWindowTitle(tr("Snake"));
    resize(550, 370);
}

MainWindow::~MainWindow() {}

QLabel *MainWindow::createLabel(const QString &text) {
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

