#pragma once

/**
 * @file TSnake.h
 * @brief TSnake
 * @author Чугайнов С.В.
 * @date 11.05.2018
 *
 *
 */

#include <vector>
#include <algorithm>

#include "Point.h"
#include "Way.h"

#include "ISnake.h"


template <class T_Snake> class TModel;

template <class T_Point>
class TSnake : public ISnake
{
    template <class T_Snake> friend class TModel;
public:

    TSnake() {}

    virtual ~TSnake() {
        m_snake.clear();
    }

    virtual bool generateNewHead(Point _sizeField) {
        T_Point newHead = T_Point(_sizeField.getX() / 2, _sizeField.getY() / 2);
        if (!m_snake.empty()) {
            newHead = m_snake.front();
            newHead += m_way.getPoint();

            if (!newHead.between(_sizeField))
                return false;

            if (!checkPoint(newHead))
                return false;
        }
        addNewHead(newHead);
        return true;
    }

    virtual void addNewHead(T_Point _newHead) {
            m_snake.insert(m_snake.begin(), _newHead);
    }

    virtual bool checkPoint(Point & _point) {   // проверка для головы новых кроликов
        return std::find(m_snake.begin(), m_snake.end(), _point) == m_snake.end();
    }

    virtual void removeTail(int _count) {
        while (_count-- > 0 && !m_snake.empty())
            m_snake.pop_back();
    }

//    virtual void start(Point _sizeField) {
//        clear();
//        m_way = Way::LEFT;
//        generateNewHead(_sizeField);
//        generateNewHead(_sizeField);
//    }


    virtual unsigned int size() const {return m_snake.size();}
    virtual bool empty() const {return m_snake.empty();}
    virtual void clear() {m_snake.clear();}

    inline typename std::vector<T_Point>::reverse_iterator rbegin() {return m_snake.rbegin();}
    inline typename std::vector<T_Point>::reverse_iterator rend() {return m_snake.rend();}

    inline typename std::vector<T_Point>::iterator begin() {return m_snake.begin();}
    inline typename std::vector<T_Point>::iterator end() {return m_snake.end();}

    inline T_Point & front() {return m_snake.front();}

protected:
    std::vector<T_Point> m_snake;

};

