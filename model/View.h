#pragma once

/*

	Тут весь вывод на экран и получения реакции от игрока

*/

#include <vector>

#include "Point.h"
#include "Way.h"


class Control;
class Rabbit;

class View
{
public:
	View(void);
	virtual ~View(void);

    void setControl(Control*);
    void setSnake(std::vector<Point> *);
    void setRabbits(std::vector<Rabbit> *);

	virtual void paint();
	
	virtual int getHieghtField() = 0;
	virtual int getWigthField() = 0;

	void setHieght(int);
	void setWigth(int);

    virtual void beforeGame() = 0;
    
private:

	int m_hieght;
	int m_wigth;
    
protected:

    Control *m_control;
    std::vector<Point> * m_snake;
    std::vector<Rabbit> * m_rabbits;
    Way m_way;
    
    virtual void beforePaintField() = 0;
    virtual void afterPaintField() = 0; 
    virtual void paintWay() = 0;
    virtual void paintSnake() = 0;
    virtual void paintRabbit(Rabbit &) = 0;
};
