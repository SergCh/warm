#pragma once

/**
 * @file Snake.h
 * @brief Snake
 * @author Чугайнов С.В.
 * @date 11.05.2018
 *
 *
 */

#include <vector>
#include <algorithm>

#include "Point.h"

class Snake
{
public:
    Snake();

    virtual ~Snake() {
        m_snake.clear();
    }

    virtual void addNewHead(Point _newHead) {
//        bool result = checkNewHead(_newHead);
//        if (result)
            m_snake.insert(m_snake.begin(), _newHead);
//        return result;
    }

    virtual bool checkPoint(Point & _point) {   // проверка для головы новых кроликов
        return std::find(m_snake.begin(), m_snake.end(), _point) == m_snake.end();
    }

    virtual void removeTail(int _count);

    virtual unsigned int size() const {return m_snake.size();}
    virtual bool empty() const {return m_snake.empty();}
    std::vector<Point> & data() {return m_snake;}
    void clear() {m_snake.clear();}

    Point & front() {return m_snake.front();}

private:
    std::vector<Point> m_snake;


};

