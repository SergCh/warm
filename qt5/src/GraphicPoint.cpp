#include <vector>
#include <algorithm>

#include <QRect>
#include <QSize>

#include "GraphicPoint.h"

#include "Point.h"
#include "Way.h"

GraphicPoint GraphicPoint::getHead(Point & _point, int _step, Way _way) {
    GraphicPoint e(HEAD, _point, _step);
    e.setPosition(_way);
    return e;
}

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

std::pair<QRect, QRect> GraphicPoint::getRects(const QSize & squareSize) {
    QRect body1(m_point.getX() * squareSize.width(), m_point.getY() * squareSize.height(),
                squareSize.width(), squareSize.height());
    QRect body2;
    int ddx = squareSize.width() / 5, ddx2 = ddx + ddx;
    int ddy = squareSize.height() / 5, ddy2 = ddy + ddy;

    switch (m_type) {
    case HEAD:
        break;

    case HORISONTAL:
        body1.translate(0, ddy * m_position);
        body1.setHeight(squareSize.width() - ddy2);
        break;

    case VERTICAL:
        body1.translate(ddx * m_position, 0);
        body1.setWidth(squareSize.height() - ddx2);
        break;

    case CORNER:
        body1.setSize(squareSize - QSize(ddx2, ddy2));
        if (m_position) {
            body2 = body1.translated(m_toLeft ? 0:ddx2, ddy);
            body1.translate(ddx, m_toUp ? 0:ddy2);
            break;
        }
        body1.translate(m_toLeft ? 0 : ddx2, m_toUp ? 0 : ddy2);
        break;
    }

    return std::make_pair(body1, body2);
}


void GraphicPoint::addHead(std::vector<GraphicPoint> & gSnake, Point & _head, Way _way, int _removed){

    GraphicPoint newHead = GraphicPoint::getHead(_head, gSnake.size() == 0 ? 0 : (gSnake.front().getStep()+1) & 3 , _way);

    if (gSnake.size() != 0) {
        GraphicPoint * pred = &newHead;
        std::vector<GraphicPoint>::iterator curr = gSnake.begin();
        std::vector<GraphicPoint>::iterator next = curr + 1;
        if (next == gSnake.end())
            next = curr;

        if (next->getY() == pred->getY()) {
            curr->changeToHorisontal();

        } else if (next->getX() == pred->getX()) {
            curr->changeToVertical();

        } else {
            const bool toLeft = (next->getX() + pred->getX() - 2 * curr->getX()) < 0;
            const bool toUp   = (next->getY() + pred->getY() - 2 * curr->getY()) < 0;

            curr->changeToCorner(toLeft, toUp);

            if (curr->getPosition() == 1) {
                    if (_way.isHorisontal()) newHead.setStep(toUp? 2:0);   //Определяем новое положение головы
                    else                     newHead.setStep(toLeft? 2:0);
            }
        }
    }

    gSnake.insert(gSnake.begin(), newHead);
    while (gSnake.size() > 0 && _removed-- > 0)
        gSnake.pop_back();
}
