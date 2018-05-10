#pragma once

/**
 *      @file
 *      @brief Пути (напрвления) движения червя
 *      @author Чугайнов С.В.
 *      @date 10.05.2018
 *
 */


#include "Point.h"

/// Направления движения
//typedef enum {
//    UP,         ///< Вверх
//    DOWN,       ///< Вниз
//    LEFT,       ///< Влево
//    RIGHT,      ///< Вправо
//    COUNT_WAYS  ///< Количество направлений
//} Way;

/// Константы для инкрементных операций при движении в направлении на еденицу

class Way {
public:
    typedef enum {
        UP,         ///< Вверх
        DOWN,       ///< Вниз
        LEFT,       ///< Влево
        RIGHT,      ///< Вправо
        COUNT_WAYS  ///< Количество направлений
    } EWay;

    Way(EWay _way=LEFT):m_way(_way) {}

    inline bool isHorisontal() const {
        return m_way == LEFT || m_way == RIGHT;
    }
    static Point POINTS_WAY[COUNT_WAYS];

    inline EWay getWay() const {return m_way;}
    inline void setWay(EWay _way) {m_way = _way;}

    static const Point & getPoint(Way & _way) {
        return Way::POINTS_WAY[_way.getWay()];
    }

private:
    EWay m_way;
};
