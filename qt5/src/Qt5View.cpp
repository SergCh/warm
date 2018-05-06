#include "Qt5View.h"

#include "Qt5Board.h"
#include "Control.h"

Qt5View::Qt5View() {
    m_board = 0;
    snakeChanged = true;    //set 0
}

void Qt5View::paint() {
    if (m_board == 0) return;
    m_board->update();
    if (snakeChanged)
        emit m_board->scoreChanged(m_snake->size());
}

int Qt5View::getHieghtField() {
    return BOARD_HEIGHT;
}

int Qt5View::getWigthField() {
    return BOARD_WIDTH;
}

void Qt5View::command(Way _way) {
    if (m_control)
        m_control->changeWay(_way);
}

void Qt5View::restart() {
    if (m_control)
        m_control->restart();
}

bool Qt5View::isPause() {
    if (!m_control)
        return true;
    return m_control->isPause();
}

void Qt5View::nextStep() {
    if (m_snake) {
        const unsigned int len = m_snake->size();
        m_control->nextStep();
        snakeChanged = len != m_snake->size();
    } else {
        snakeChanged = false;
    }
}

void Qt5View::beforeGame() {

}

