
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
