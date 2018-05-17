
#include <algorithm>
#include "RabbitFactory.h"
#include "Rabbit.h"
#include "Config.h"

/**
 * @brief The checkPoint struct is Функтор для std::find_if
 */
struct checkPoint
{
  checkPoint( Point p ) : m_p(p) {}
  bool operator()( const Rabbit & rabbit ) const {
    return rabbit.check(m_p);
  }
  Point m_p;
};

/**
 * @brief The checkDead struct is Функтор для std::find_if
 */
struct checkDead
{
//  checkDead(){}
  bool operator()( const Rabbit & rabbit ) const {
    return rabbit.isDead();
  }
};


RabbitFactory::RabbitFactory() {
    m_rabbits.reserve(10);
}

void RabbitFactory::newRabbit(Point & _size, std::vector<Point> & _snake) {
    int times=100;
    Point point(std::rand() % _size.getX(), std::rand() % _size.getY());
    do {

        if (/*_snake.checkPoint(point) &&*/
            std::find_if(m_rabbits.begin(), m_rabbits.end(), checkPoint(point)) == m_rabbits.end()) {
                Rabbit rabbit(point, getLive(), getWeight());
                m_rabbits.push_back(rabbit);
                break;
        }

        int x = point.getX();
        int y = point.getY();
        if (++x >= _size.getX()) {
            x=0;
            if (++y >= _size.getY()) {
                y=0;
            }
        }
        point.setXY(x, y);

    } while(--times > 0);   //защита от зависания
    // сюда бы сообщение для отладки, что добавить не может
}


int RabbitFactory::eat(Point & _head) {
    int weight=0;

    for (std::vector<Rabbit>::iterator iter = m_rabbits.begin(); iter != m_rabbits.end(); iter++) {
        iter->eat(_head);
        if (iter->isDead())
            weight += iter->getWeight();
    }

    m_rabbits.erase(std::remove_if(m_rabbits.begin(), m_rabbits.end(), checkDead()), m_rabbits.end());

    return weight;
}



