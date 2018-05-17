#pragma once
/**
 * @file isnake
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 17.05.2018
 *
 *
 */

#include "Point.h"
#include "Way.h"

class ISnake
{
public:

    friend class Model;

    ISnake() {}

    virtual ~ISnake() {}

    virtual bool generateNewHead(Point _sizeField) = 0;

    virtual bool checkPoint(Point & _point) = 0;

    inline Way getWay() const {return m_way;}

    virtual void clear() = 0;

    virtual unsigned int size() const = 0;

    virtual void removeTail(int _count) = 0;
    virtual Point & front() = 0;



    virtual void start(Point _sizeField) {
        clear();
        m_way = Way::LEFT;
        generateNewHead(_sizeField);
        generateNewHead(_sizeField);
    }


protected:
    Way m_way;
};

