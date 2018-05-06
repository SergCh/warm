#ifndef QT5BOARD_H
#define QT5BOARD_H

#include <QFrame>
#include <QBasicTimer>

QT_BEGIN_NAMESPACE
//class QSize;
QT_END_NAMESPACE


class Qt5View;

class Qt5Board: public QFrame {

    Q_OBJECT

public:
    Qt5Board(Qt5View * _view, QWidget *parent = 0);

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    QSize getSquareSize();
    int timeoutTime() { return 100; }

public slots:
    void restart();

signals:
    void scoreChanged(int score);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:

    Qt5View *m_view;
    QBasicTimer timer;
    int step;


public:
    void pause(bool p);
};



#endif

