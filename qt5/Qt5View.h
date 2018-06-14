#ifndef QT5VIEW_H
#define QT5VIEW_H

#include <QFrame>
#include <QBasicTimer>

#include <vector>

#include "IView.h"
#include "Way.h"
#include "Point.h"
#include "GraphicPoint.h"
#include "GraphicSnake.h"
#include "TGraphicView.h"

using namespace Snake;

class Qt5View : public QFrame, public TGraphicView<Qt5View>
{

    Q_OBJECT


public:
    Qt5View(QWidget *parent = 0);

    virtual void beforeGame();
    virtual void paint();
    virtual void changeScore(int _score);

    void nextStep();

public slots:
    void restart();

signals:
    void scoreChanged(int score, int =0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;
    void timerEvent(QTimerEvent *event) Q_DECL_OVERRIDE;

public:
    void fillRectangle(int _x, int _y, int _w, int _h, int _c);
    void drawLine(int _x1, int _y1, int _x2, int _y2, int _c);
    void drawTextPause();
    int getSquareSize();

private:

    QColor getColor(unsigned int _c);

    QPainter  * m_painter;  // save in paintEvent for draw primitives

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    QBasicTimer timer;

#ifdef QT_DEBUG
    void pause(bool p);
#endif

};

#endif // QT5VIEW_H
