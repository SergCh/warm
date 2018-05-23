#pragma once

/**
 *      @file Point.h
 *      @brief Класс координаты отображаемых элементов
 *      @author Чугайнов С.В.
 *      @date 09.05.2018
 *      @todo Нужен рефакторинг имен методов
 *
 * Класс координат отображаемых элементов, наследован от std::pair<int, int>
 * Коорлината X - first
 * Коорлината Y - second
 */

#include <utility>

namespace Snake {

    class Point: public std::pair<int, int> {

    public:
        /**
         * @brief Point Конструктор
         * @param _x Коорлината X
         * @param -y Координата Y
         */
        Point(int _x, int _y);

        /**
         * @brief Point Конструктор поумолчанию координаты ставятся в (0,0)
         */
        Point();

        /**
         * @brief setXY Установка координат
         * @param _x Координата X
         * @param _y Координата Y
         */
        void setXY(int _x, int _y);

        /**
         * @brief getX Получить координату X
         * @return  Координату X
         */
        inline int getX() const {return first;}

        /**
         * @brief getY Получить координату Y
         * @return Координту Y
         */
        inline int getY() const {return second;}

        /**
         * @brief between Проверяет находится ли точна между точками (НЕ ВКЛЮЧИТЕЛЬНО)
         * @param low Нижняя точка
         * @param high Верхняя точка
         * @return Находится ли точна между точками (НЕ ВКЛЮЧИТЕЛЬНО)
         *
         * Координаты точки low дожны дыть не больше координат точки hight
         * Метод нигде в модели не исмоьлзуется, только в следующем методе
         * рассмотреть нужность его
         */
        bool between(Point& low , Point& hight);

        /**
         * @brief between Проверяет находится ли точна между (-1, -1) и hight (НЕ ВКЛЮЧИТЕЛЬНО)
         * @param hight Верхняя точка
         * @return Проверяет находится ли точна между (-1, -1) и hight (НЕ ВКЛЮЧИТЕЛЬНО)
         * @todo Имя не соответствует, необходим рефаторинг
         */
        bool between(Point& hight);

        /**
         * @brief operator += Добавляем координаты и возвращаяем ссылку на this
         * @return ссылку на this с результом операции
         */
        Point& operator += (const Point& _point);

        /**
         * @brief less Проверяем меньше ли эта точка чем _point
         * @param _point Точка для сравнивания
         * @return Результат проверки: меньше ли эта точка чем _point
         * @todo Метод используется только в методе between, нужен ли?
         */
        bool less (const Point& _point);
    };

}
