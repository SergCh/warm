#ifndef QT5VIEW_H
#define QT5VIEW_H

#include <QFrame>
#include <QBasicTimer>

#include <vector>

#include "View.h"
#include "Way.h"
#include "Point.h"
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

    QBasicTimer timer;

    std::vector<GraphicPoint> gSnake;

#ifdef QT_DEBUG
    void pause(bool p);
#endif

};

#endif // QT5VIEW_H
