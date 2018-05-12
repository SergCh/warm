#pragma once

/**
 * @file GraphicSnake.h
 * @brief GraphicSnake
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */

#include "Snake.h"
#include "GraphicPoint.h"

class GraphicSnake : public Snake<GraphicPoint>
{
public:
    GraphicSnake();
};

