#pragma once

/**
 * @file config
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */


#include "Point.h"
#include "TSnake.h"

template <class TSnake> class TModel;

typedef TSnake<Point> Snake;
typedef TModel<Snake> Model;
