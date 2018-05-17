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

    ISnake() {}

    virtual ~ISnake() {}

    virtual bool generateNewHead(Point _sizeField) = 0;

    virtual bool checkPoint(Point & _point) = 0;

    inline Way getWay() const {return m_way;}

protected:
    Way m_way;
};

