#pragma once

/**
 * @file config
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */


//#include "Model.h"
#include "Point.h"
#include "GraphicPoint.h"
#include "Snake.h"
#include "GraphicSnake.h"

//class GraphicPoint;
//class GraphicSnake;

template <class TSnake> class TModel;

//typedef Snake<Point> SnakePoint;
//typedef Model<SnakePoint> ModelSnake;


//#include "GraphicSnake.h"
//#include "Model.h"


typedef GraphicSnake SnakePoint;
typedef TModel<SnakePoint> ModelSnake;
