#include <vector>
#include <algorithm>

#include "GraphicPoint.h"

using namespace Snake;

void GraphicPoint::changeToHorisontal() {
    m_type = HORISONTAL;
    setPosition(m_step == 3 ? 1 : m_step);
}

void GraphicPoint::changeToVertical() {
    m_type = VERTICAL;
    setPosition(m_step == 3 ? 1 : m_step);
}

void GraphicPoint::changeToCorner(bool _toLeft, bool _toUp) {
    m_type = CORNER;
    setPosition(m_step & 1);
    m_toLeft =_toLeft;
    m_toUp = _toUp;
}


