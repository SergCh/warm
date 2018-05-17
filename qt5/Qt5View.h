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

class Qt5View : public QFrame, public IView /*<GraphicSnake>*/
{

    Q_OBJECT


public:
    Qt5View(QWidget *parent = 0);

    virtual int getHieghtField();
    virtual int getWidthField();
    virtual void setSnake(ISnake * _snake);

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

private:
    enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50, MAX_PATH = 10 };

    void drawSnake(GraphicPoint* _point, const QSize & _squareSize, QPainter * _painter, QColor _color);

    QSize sizeHint() const Q_DECL_OVERRIDE;
    QSize minimumSizeHint() const Q_DECL_OVERRIDE;

    QSize getSquareSize();
    inline int timeoutTime() const { return 100; }
    GraphicSnake * m_snake;


    QBasicTimer timer;

#ifdef QT_DEBUG
    void pause(bool p);
#endif

};

#endif // QT5VIEW_H
