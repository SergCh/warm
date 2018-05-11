#pragma once

#include <vector>
#include <algorithm>

#include <QRect>
#include <QSize>

#include "Point.h"
#include "Way.h"

QT_BEGIN_NAMESPACE
class QRect;
class QSize;
class QPainter;
QT_END_NAMESPACE


class GraphicPoint {

public:
    typedef enum {
        HEAD,
        HORISONTAL,
        VERTICAL,
        CORNER
    } Type;

    GraphicPoint(Type _type, Point & _point, int _step) {
        m_type = _type, m_point = _point; m_step= _step;
    }

    inline void setPosition(int _position) {
        m_position = _position;
    }

    inline void setPosition(int _position, bool _toLeft, bool _toUp) {
        m_position = _position; m_toLeft = _toLeft; m_toUp = _toUp;
    }

    inline int getStep() const {
        return m_step;
    }

    inline void setStep(int _step) {
        m_step = _step;
    }

    inline int getPosition() const {
        return m_position;
    }

    inline int getX() const {
        return m_point.getX();
    }

    inline int getY() const {
        return m_point.getY();
    }

    void draw(const QSize & _squareSize, QPainter * _painter, int _index);

    static GraphicPoint getHead(Point & _point, int _step, Way _way);

    void changeToHorisontal();

    void changeToVertical();

    void changeToCorner(bool _toLeft, bool _toUp);

    static void addHead(std::vector<GraphicPoint> & gSnake, Point & _head, Way _way, int _removed);

private:
    Point m_point;
    int m_step;
    Type m_type;
    int m_position;
    bool m_toLeft;
    bool m_toUp;
};
