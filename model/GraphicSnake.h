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
    enum {MAX_PATH = 20};

    GraphicSnake(): TSnake<GraphicPoint>() {
        m_path.reserve(MAX_PATH+3);
    }

    virtual void addNewHead(GraphicPoint _newHead) {

        int step = 0;
        _newHead.setPosition(m_way);

        if (!empty()) {
            step = (front().getStep() + 1) & 3;
            GraphicPoint * pred = &_newHead;
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
                    if (m_way.isHorisontal()) step = toUp ? 2 : 0;   //Определяем новое положение головы
                    else                      step = toLeft ? 2 : 0;
                }
            }
        }

        _newHead.setStep(step);
        TSnake::addNewHead(_newHead);
    }

    virtual void removeTail(int _count) {
        while (_count-- > 0 && !m_snake.empty()) {
            GraphicPoint point = m_snake.back();
            m_path.insert(m_path.begin(), point);
            m_snake.pop_back();
        }

        while (m_path.size() > MAX_PATH) {
            m_path.pop_back();
        }
    }

    inline std::vector<GraphicPoint>::iterator beginPath() {return m_path.begin();}
    inline std::vector<GraphicPoint>::iterator endPath() {return m_path.end();}
    inline std::vector<GraphicPoint>::reverse_iterator rbeginPath() {return m_path.rbegin();}
    inline std::vector<GraphicPoint>::reverse_iterator rendPath() {return m_path.rend();}
    inline int sizePath() const {return m_path.size();}

    virtual void start(Point _sizeField) {
        m_path.clear();
        TSnake<GraphicPoint>::start(_sizeField);
    }

private:
    std::vector<GraphicPoint> m_path;

};

