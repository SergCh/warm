/**
 * @file GraphicSnake.cpp
 * @brief GraphicSnake
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */

#include "GraphicSnake.h"

using namespace SNAKE_MODEL;



GraphicSnake::GraphicSnake(): TSnake<GraphicPoint>() {
    m_maxPath = 0;
}

void GraphicSnake::addNewHead(GraphicPoint _newHead) {

    int step = 0;
    _newHead.setPosition(m_way);

    if (!empty()) {
        step = (front().getStep() + 1) & 3;
        std::vector<GraphicPoint>::iterator curr = begin();
        std::vector<GraphicPoint>::iterator next = curr + 1;
        if (next == end())
            next = curr;

        if (next->getY() == _newHead.getY()) {
            curr->changeToHorisontal();

        } else if (next->getX() == _newHead.getX()) {
            curr->changeToVertical();

        } else {
            const bool toLeft = (next->getX() + _newHead.getX() - 2 * curr->getX()) < 0;
            const bool toUp   = (next->getY() + _newHead.getY() - 2 * curr->getY()) < 0;

            curr->changeToCorner(toLeft, toUp);

            if (curr->getPosition() == 1) {
                if (m_way.isHorisontal()) step = toUp ? 2 : 0;   //Определяем новое положение головы
                else                      step = toLeft ? 2 : 0;
            }
        }
    }

    _newHead.setStep(step);
    TSnake::addNewHead(_newHead);
}

void GraphicSnake::removeTail(int _count) {

    while (_count-- > 0 && !m_snake.empty()) {
        GraphicPoint point = m_snake.back();
        m_path.insert(m_path.begin(), point);
        m_snake.pop_back();
    }

    while (m_path.size() > m_maxPath) {
        m_path.pop_back();
    }
}

void GraphicSnake::start(Point _sizeField) {
    m_path.clear();
    ISnake::start(_sizeField);
}

void GraphicSnake::setMaxPath(unsigned int _maxPath) {
    if (_maxPath == m_maxPath)
        return;
    m_maxPath = _maxPath;
    if (m_maxPath > 0)
        m_path.reserve(m_maxPath+3);
}
