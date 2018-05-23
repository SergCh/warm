#pragma once

/**
 *      @file Rabbit.h
 *      @brief Класс кролик
 *      @author Чугайнов С.В.
 *      @date 09.05.2018
 *      @todo Завести единого предка предка, который будет нести информацию, отображаемого елемента
 *      @todo Может создать интерфейсный класс, без наворотов
 *
*/


#include <utility>

#include "Point.h"

namespace Snake {

    class Rabbit : public Point
    {

    public:

        /**
         * @brief Rabbit Конструктор
         * @param _point Координаты
         * @param _live Время жизни, при -1 сам не умерает.
         * @param _weight Колличество элементов добавляемых змею при поедания этого кролика
         */
        Rabbit(Point _point, int _live = -1, int _weight = 5)
            : m_live(_live), m_weight(_weight) {
            setXY(_point.getX(), _point.getY());
        }

        /**
         * @brief isDead Возвращает кончились ли жизни у кролика
         * @return Мертый ли кролик
         */
        bool isDead() const {return m_live == 0;}

        /**
         * @brief getWeight Возвращает количество добавляемых элементов змею при поедания этого кролика
         * @return Количество добавляемых элементов змею при поедания этого кролика
         */
        int getWeight() const {return m_weight;}

        /**
         * @brief eat Проверка на съедение кролика
         * @param _head Координаты головы червя
         *
         * Проверяем координаты если съел, устанавливаем флаг, что кролик мертвый _live=0
         * Уменьшаем жизнь на еденицу. Если кролик умер сам, то вес обнуляем (_weight=0)
         * Незабываем пройтись по массиву кроликов и подчистить те у которых _live==0
         */
        void eat(const Point & _head);

        /**
         * @brief check Проверка на совпадение координат
         * @param _point Координаты головы змея
         * @return совпили ли координаты
         */
        bool check(const Point & _point) const {return getX() == _point.getX() && getY() == _point.getY();}

    private:

        /// Количество жизней
        int m_live;

        /// Вес кролика
        int m_weight;

    };

}
