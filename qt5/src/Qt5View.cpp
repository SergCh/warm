#include "Qt5View.h"

#include "Qt5Board.h"
#include "Control.h"

Qt5View::Qt5View() {
    m_board = 0;
}

void Qt5View::paint() {
    if (m_board == 0) return;
    m_board->update();
    emit m_board->scoreChanged(m_snake->size());
}

int Qt5View::getHieghtField() {
    return BOARD_HEIGHT;
}

int Qt5View::getWigthField() {
    return BOARD_WIDTH;
}

void Qt5View::command(Way _way) {
    if (m_control != 0)
        m_control->changeWay(_way);
}

void Qt5View::restart() {
    if (m_control != 0)
        m_control->restart();
}

bool Qt5View::isPause() {
    if (m_control == 0)
        return true;
    return m_control->isPause();
}


bool Qt5View::nextStep() {
    if (m_control == 0)
        return true;
    m_control->nextStep();
    return true;
}

void Qt5View::beforeGame() {

}

void Qt5View::afterPaintField() {
//    if (m_board == 0) return;
//    m_board->update();
//    emit m_board->scoreChanged(m_snake->size());
}

void Qt5View::beforePaintField() {

}

void Qt5View::paintRabbit(Rabbit &) {

}

void Qt5View::paintSnake() {

}

void Qt5View::paintWay() {

}

