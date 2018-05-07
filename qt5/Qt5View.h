#ifndef QT5VIEW_H
#define QT5VIEW_H

#include <QFrame>
#include <QBasicTimer>

QT_BEGIN_NAMESPACE
//class QSize;
QT_END_NAMESPACE

#include <vector>

#include "View.h"
#include "Way.h"
#include "Point.h"
#include "Control.h"

class Qt5View : public QFrame, public View
{

    Q_OBJECT


public:
    Qt5View(QWidget *parent = 0);

    virtual int getHieghtField();
    virtual int getWigthField();

    virtual void beforeGame();
    virtual void paint();

    void nextStep();

public slots:
    void restart();

signals:
    void scoreChanged(int score);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50 };

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    QSize getSquareSize();
    int timeoutTime() { return 100; }

    void incStep(int & _step) const { _step = (_step+1) & 3;}
//    void decStep(int & _step) { _step = (_step+3) & 3;}


    bool snakeChanged;
    QBasicTimer timer;
    int step;

public:

#ifdef QT_DEBUG
    void pause(bool p);
#endif

};

#endif // QT5VIEW_H
