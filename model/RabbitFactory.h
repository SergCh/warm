#pragma once

#include <vector>
#include "Rabbit.h"
#include "Point.h"

class RabbitFactory
{
public:
    RabbitFactory();

    void clear();
    void newRabbit(Point & size, std::vector<Point> & occuped);
    void step();
    int eat(Point &);

    int getLive() const {return 134;}
    int getWeight() const {return 5;}

    std::vector<Rabbit> & getData();

private:
    std::vector<Rabbit> m_rabbits;
};

