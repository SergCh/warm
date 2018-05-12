#include <vector>
#include <algorithm>

#include <QRect>
#include <QSize>
#include <QColor>
#include <QPainter>

#include "GraphicPoint.h"

#include "Point.h"
#include "Way.h"

GraphicPoint GraphicPoint::getHead(Point & _point, int _step, Way _way) {
    GraphicPoint head(_point.getX(), _point.getY(), HEAD, _step);
    head.setPosition(_way);
    return head;
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


void GraphicPoint::draw(const QSize & _squareSize, QPainter * _painter, int _index) {
    QRect body1(getX() * _squareSize.width(), getY() * _squareSize.height(),
                _squareSize.width(), _squareSize.height());

    const QColor color = _index % 5 == 3 ? Qt::yellow: Qt::red;

    int ddx = _squareSize.width() / 5, ddx2 = ddx + ddx;
    int ddy = _squareSize.height() / 5, ddy2 = ddy + ddy;

    switch (m_type) {
    case HEAD:
        _painter->fillRect(body1, color);
        return;

    case HORISONTAL:
        body1.translate(0, ddy * m_position);
        body1.setHeight(_squareSize.width() - ddy2);
        _painter->fillRect(body1, color);
        return;

    case VERTICAL:
        body1.translate(ddx * m_position, 0);
        body1.setWidth(_squareSize.height() - ddx2);
        _painter->fillRect(body1, color);
        break;

    case CORNER:
        body1.setSize(_squareSize - QSize(ddx2, ddy2));
        if (m_position) {

            QRect body2 = body1.translated(m_toLeft ? 0:ddx2, ddy);
            _painter->fillRect(body2, color);

            body1.translate(ddx, m_toUp ? 0:ddy2);
            _painter->fillRect(body1, color);

            return;
        }
        body1.translate(m_toLeft ? 0 : ddx2, m_toUp ? 0 : ddy2);
        _painter->fillRect(body1, color);
        return;
    }
}

