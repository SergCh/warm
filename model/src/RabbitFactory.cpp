
#include <algorithm>
#include "RabbitFactory.h"
#include "Rabbit.h"

RabbitFactory::RabbitFactory() {

}

void RabbitFactory::clear() {
    m_rabbits.clear();
}

void RabbitFactory::step() {

    for (std::vector<Rabbit>::iterator iter=m_rabbits.begin(); iter != m_rabbits.end(); iter++)
        iter->step();

    bool finded;
    do {
        finded = false;
        std::vector<Rabbit>::iterator iter;
        if ((iter=std::find_if(m_rabbits.begin(), m_rabbits.end(), Rabbit::checkDead())) != m_rabbits.end()) {
            m_rabbits.erase(iter);
            finded = true;
        }
    } while (finded);
}

std::vector<Rabbit> & RabbitFactory::getData() {
    return m_rabbits;
}

void RabbitFactory::newRabbit(Point & size, std::vector<Point> & occuped) {
    int times=100;
    Point point(std::rand() % size.getX(), std::rand() % size.getY());
    do {

        if (std::find(occuped.begin(), occuped.end(), point) == occuped.end() &&
            std::find_if(m_rabbits.begin(), m_rabbits.end(), Rabbit::checkPoint(point)) == m_rabbits.end()) {
                Rabbit rabbit(point, getLive(), getWeight());
                m_rabbits.push_back(rabbit);
                break;
        }

        int x = point.getX();
        int y = point.getY();
        if (++x >= size.getX()) {
            x=0;
            if (++y >= size.getY()) {
                y=0;
            }
        }
        point.setXY(x, y);

    } while(--times > 0);   //защита от зависания
    // сюда бы сообщение для отладки, что добавить не может
}


int RabbitFactory::eat(Point & _point) {
    int weight=0;

    std::vector<Rabbit>::iterator iter;
    if ((iter=std::find_if(m_rabbits.begin(), m_rabbits.end(), Rabbit::checkPoint(_point))) != m_rabbits.end()) {
        weight = iter->getWeight();
        m_rabbits.erase(iter);
    }
    return weight;
}
