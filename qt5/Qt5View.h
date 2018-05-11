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
#include "GraphicPoint.h"

class Qt5View : public QFrame, public View
{

    Q_OBJECT


public:
    Qt5View(QWidget *parent = 0);

    virtual int getHieghtField();
    virtual int getWidthField();

    virtual void beforeGame();
    virtual void paint();
    virtual void changeScore(int _score, int =0);

    void nextStep();

public slots:
    void restart();

signals:
    void scoreChanged(int score, int =0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

private:
    enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50 };

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    QSize getSquareSize();
    inline int timeoutTime() const { return 100; }

    inline void incStep(int & _step) const { _step = (_step+1) & 3;}
    inline void decStep(int & _step) const { _step = (_step+3) & 3;}


    QBasicTimer timer;

//    int step;
//    std::vector<int> steps;

    std::vector<GraphicPoint> gSnake;

#ifdef QT_DEBUG
    void pause(bool p);
#endif

};

#endif // QT5VIEW_H
