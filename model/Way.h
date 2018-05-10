#pragma once

/**
 *      @file
 *      @brief Пути (напрвления) движения червя
 *      @author Чугайнов С.В.
 *      @date 09.05.2018
 *      @todo Может в класс переделать, не знаю еще
 *
 */

class Point;

/// Направления движения
typedef enum {
    UP,         ///< Вверх
    DOWN,       ///< Вниз
    LEFT,       ///< Влево
    RIGHT,      ///< Вправо
    COUNT_WAYS  ///< Количество направлений
} Way;

/// Константы для инкрементных операций при движении в направлении на еденицу
extern const Point WAYS[COUNT_WAYS];

#define isHorisontal(W) ((W) == Way::LEFT || (W) == Way::RIGHT)
#define isVertical(W)   ((W) == Way::UP || (W) == Way::DOWN)
