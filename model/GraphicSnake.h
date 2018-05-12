#pragma once

/**
 * @file GraphicSnake.h
 * @brief GraphicSnake
 * @author Чугайнов С.В.
 * @date 12.05.2018
 *
 *
 */

#include "GraphicPoint.h"
#include "TSnake.h"

class GraphicSnake : public TSnake<GraphicPoint>
{
public:
    GraphicSnake(): TSnake<GraphicPoint>() {}

    virtual void addNewHead(Point _newHead) {

        GraphicPoint newHead = GraphicPoint::getHead(_newHead, empty() ? 0 : (front().getStep()+1) & 3, m_way);

        if (!empty()) {
            GraphicPoint * pred = &newHead;
            std::vector<GraphicPoint>::iterator curr = begin();
            std::vector<GraphicPoint>::iterator next = curr + 1;
            if (next == end())
                next = curr;

            if (next->getY() == pred->getY()) {
                curr->changeToHorisontal();

            } else if (next->getX() == pred->getX()) {
                curr->changeToVertical();

            } else {
                const bool toLeft = (next->getX() + pred->getX() - 2 * curr->getX()) < 0;
                const bool toUp   = (next->getY() + pred->getY() - 2 * curr->getY()) < 0;

                curr->changeToCorner(toLeft, toUp);

                if (curr->getPosition() == 1) {
                        if (m_way.isHorisontal()) newHead.setStep(toUp? 2:0);   //Определяем новое положение головы
                        else                     newHead.setStep(toLeft? 2:0);
                }
            }
        }

        TSnake::addNewHead(newHead);
    }
};

