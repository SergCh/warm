
#include "View.h"
#include "Control.h"
#include "Rabbit.h"

View::View() : m_control(0){
    m_rabbits = 0;
    m_snake = 0;
    m_way = Way::LEFT;
}

View::~View() {
}

void View::setControl(Control* _control) {
    m_control = _control;
}

void View::setSnake(std::vector<Point>* _snake) {
    m_snake = _snake;
}

void View::setRabbits(std::vector<Rabbit>* _rabbits) {
    m_rabbits = _rabbits;
}

void View::paint() {
	if (getHieghtField()<=0 || getWigthField()<=0)
		return;
    
	m_way = m_control->getWay();

    beforePaintField();

    if (m_snake != 0 && m_snake->size() > 0) {
        paintWay();
        paintSnake();
    }

    if (m_rabbits != 0)
        for (std::vector<Rabbit>::iterator iter=m_rabbits->begin(); iter != m_rabbits->end(); iter++)
            paintRabbit(*iter);
    
    afterPaintField();
}
