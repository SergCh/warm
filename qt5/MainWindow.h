#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFrame>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLCDNumber;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Qt5View;

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(Qt5View *view, QWidget *parent = 0);
    ~MainWindow();

private:
    QLabel *createLabel(const QString &text);

    Qt5View *board;
    QLCDNumber *scoreLcd;
    QPushButton *quitButton;
    QPushButton *startButton;
};

#endif // MAINWINDOW_H
