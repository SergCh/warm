#pragma once

/**
 *      @file
 *      @brief Класс кролик
 *      @author Чугайнов С.В.
 *      @date 09.05.2018
 *      @todo Завести единого предка предка, который будет нести информацию, отображаемого елемента
 *      @todo Может создать интерфейсный класс, без наворотов
 *
*/


#include <utility>

#include "Point.h"
class Rabbit
{

public:

    /**
     * @brief Rabbit Конструктор
     * @param _point Координаты
     * @param _live Время жизни, при -1 сам не умерает.
     * @param _weight Колличество элементов добавляемых змею при поедания этого кролика
     */
    Rabbit(Point _point, int _live = -1, int _weight = 5)
        :m_point(_point), m_live(_live), m_weight(_weight) {}

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
     * @brief getPoint Возвращает координаты кролика
     * @return Координаты кролика
     */
    const Point &getPoint() const {return m_point;}

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
    bool check(const Point & _point) const {return m_point == _point;}

    /**
     * @brief getX Возвращает координату X
     * @return Координату X
     */
    int getX() const {return m_point.getX();}

    /**
     * @brief getY Возвращает коорлинату Y
     * @return Координату Y
     */
    int getY() const {return m_point.getY();}

private:

    /// Координата кролика
    Point m_point;

    /// Количество жизней
    int m_live;

    /// Вес кролика
    int m_weight;

public:

    /**
     * @brief The checkPoint struct is Функтор для std::find_if
     */
    struct checkPoint
    {
      checkPoint( Point p ) : m_p(p) {}
      bool operator()( const Rabbit & rabbit ) const
      {
        return rabbit.check(m_p);
      }
    private:
      Point m_p;
    };

    /**
     * @brief The checkDead struct is Функтор для std::find_if
     */
    struct checkDead
    {
      checkDead(){}
      bool operator()( const Rabbit & rabbit ) const
      {
        return rabbit.isDead();
      }
    };

};

