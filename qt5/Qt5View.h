#ifndef QT5VIEW_H
#define QT5VIEW_H

#include <vector>

#include "View.h"
#include "Way.h"
#include "Point.h"
#include "Control.h"

class Qt5Board;

class Qt5View : public View
{
public:
    Qt5View(/*QWidget *parent = 0*/);

    virtual int getHieghtField();
    virtual int getWigthField();

    virtual void beforeGame();

    void setBoard(Qt5Board * _board) {m_board = _board;}

    std::vector<Point> * getSnake() const {return m_snake;}
    std::vector<Rabbit> * getRabbits() const {return m_rabbits;}
    Way getWay() const {return m_control->getWay();}

    void command(Way);

    virtual void paint();

    bool nextStep();
    void restart();

    bool isPause();

protected:
    virtual void afterPaintField();
    virtual void beforePaintField();
    virtual void paintRabbit(Rabbit &);
    virtual void paintSnake();
    virtual void paintWay();

private:
    enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50 };
    Qt5Board* m_board;
};

#endif // QT5VIEW_H
