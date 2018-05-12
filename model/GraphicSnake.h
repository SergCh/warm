#pragma once

/**
 * @file GraphicSnake.h
 * @brief GraphicSnake
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */

#include "TSnake.h"
#include "GraphicPoint.h"

class GraphicSnake : public TSnake<GraphicPoint>
{
public:
    GraphicSnake(): TSnake<GraphicPoint>() {}

//    virtual void addNewHead(TPoint _newHead) {
//            m_snake.insert(m_snake.begin(), _newHead);
//    }


    virtual void addNewHead(Point _newHead) {
        GraphicPoint newHead = GraphicPoint::getHead(_newHead, 0, Way::LEFT);
        TSnake::addNewHead(newHead);
    }


};

