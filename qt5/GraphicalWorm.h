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
QT_END_NAMESPACE


class ElementSnake {

public:
    typedef enum {
        HEAD,
        HORISONTAL,
        VERTICAL,
        CORNER
    } Type;

    ElementSnake(Type _type, Point & _point, int _step) {
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


    std::pair<QRect, QRect> getRects(const QSize & squareSize);

private:
    Point m_point;
    int m_step;
    Type m_type;
    int m_position;
    bool m_toLeft;
    bool m_toUp;

public:
    static ElementSnake getHead(Point & _point, int _step, Way _way);

    void changeToHorisontal();

    void changeToVertical();

    void changeToCorner(bool _toLeft, bool _toUp);

    static void addHead(std::vector<ElementSnake> & gSnake, Point & _head, Way _way, int _removed);
};

