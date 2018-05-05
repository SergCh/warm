#ifndef RABBITFACTORY_H
#define RABBITFACTORY_H

#include <utility>

#include "Point.h"
class Rabbit
{

public:
    Rabbit(Point _point, int _live = -1, int _weight = 5)
        :m_point(_point), m_live(_live), m_weight(_weight) {}

    bool isDead() const {return m_live == 0;}
    int getWeight() const {return m_weight;}
    const Point &getPoint() const {return m_point;}
    bool step();
    bool check(const Point & _point) const {return m_point == _point;}

    int getX() const {return m_point.getX();}
    int getY() const {return m_point.getY();}

private:
    Point m_point;
    int m_live;
    int m_weight;

public:

    struct checkPoint
    {
      checkPoint( Point p ) : m_p(p) {}
      bool operator()( const Rabbit & rabbit ) const
      {
        return rabbit.check(m_p);
      }
    private:
      Point m_p;
    };

    struct checkDead
    {
      checkDead(){}
      bool operator()( const Rabbit & rabbit ) const
      {
        return rabbit.isDead();
      }
    };

};

#endif // RABBITFACTORY_H
