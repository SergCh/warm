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

template <class TPoint>
class Snake
{
public:

    Snake() {}

    virtual ~Snake() {
        m_snake.clear();
    }

    virtual void addNewHead(TPoint _newHead) {
            m_snake.insert(m_snake.begin(), _newHead);
    }

    virtual bool checkPoint(Point & _point) {   // проверка для головы новых кроликов
        return std::find(m_snake.begin(), m_snake.end(), _point) == m_snake.end();
    }

    virtual void removeTail(int _count) {
        while (_count-- > 0 && !m_snake.empty())
            m_snake.pop_back();
    }

    virtual unsigned int size() const {return m_snake.size();}
    virtual bool empty() const {return m_snake.empty();}
    std::vector<TPoint> & data() {return m_snake;}
    void clear() {m_snake.clear();}

    const Point & front() const {return m_snake.front();}

    inline typename std::vector<TPoint>::reverse_iterator rbegin() {return m_snake.rbegin();}
    inline typename std::vector<TPoint>::reverse_iterator rend() {return m_snake.rend();}

    inline typename std::vector<TPoint>::iterator begin() {return m_snake.begin();}
    inline typename std::vector<TPoint>::iterator end() {return m_snake.end();}

    inline TPoint & front() {return m_snake.front();}

protected:
    std::vector<TPoint> m_snake;
};

