#pragma once

/**
 *      @file Way.h
 *      @brief Класс пути (напрвления) движения червя
 *      @author Чугайнов С.В.
 *      @date 10.05.2018
 *
 */

#include "Point.h"

namespace Snake {

    class Way {
    public:

        /// Направления движения
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

        /// Константы для инкрементных операций при движении в направлении на еденицу
        static const Point POINTS_WAY[COUNT_WAYS];

        EWay getWay() const {return m_way;}
        void setWay(EWay _way) {m_way = _way;}

        operator unsigned int () const {return (unsigned int) m_way;}

        const Point & getPoint() const {
            return Way::POINTS_WAY[m_way];
        }


    private:
        EWay m_way;
    };

}
