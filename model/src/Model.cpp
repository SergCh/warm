//#include "StdAfx.h"
#include <algorithm>

#include <cstdlib>
#include <ctime>

#include "Model.h"
#include "RabbitFactory.h"

Model::Model::Model(Point _size, RabbitFactory &_rabbits) : m_size(_size), m_rabbits(_rabbits) {
}

Model::~Model(void) {
}

void Model::init() {
    std::srand(unsigned(std::time(0)));
	m_snake.clear();
	m_rabbits.clear();
	int x = m_size.getX() / 2, y = m_size.getY() / 2;
	m_snake.push_back(Point(x, y));		// голова
	m_snake.push_back(Point(x+1, y));	// хвост
    m_way.setWay(Way::LEFT);
	m_length = 0;
    m_state = Model::GOOD_CHANGED;
}

void Model::changeWay(Way _way) {
	m_way = _way;
}

Model::State Model::move() {

    if (m_state == Model::DEAD)
        return Model::DEAD;

    const unsigned int len = m_snake.size();
	Point newHead = m_snake[0];	// голова змея
    newHead += Way::getPoint(m_way);

	if (!newHead.between(m_size))
        return Model::DEAD;

	if (std::find(m_snake.begin(), m_snake.end(), newHead) != m_snake.end())
        return Model::DEAD;

    m_length += m_rabbits.eat(newHead);

    m_snake.insert(m_snake.begin(), newHead);   // двигаем червя

    if (m_length < 0) {                         // длина змея уменьшилась
		m_snake.pop_back();
        m_snake.pop_back();
        m_length++;
    } else if (m_length == 0)                   // не изменилась длина
        m_snake.pop_back();
    else                                        // длина змея увеличилась
        m_length--;

    if (m_snake.size() < 2)                     // если осталась одна голова, то змей тоже умер
        return Model::DEAD;

    return (len == m_snake.size()) ? Model::GOOD : Model::GOOD_CHANGED;
}

void Model::addRabbit() {
    m_rabbits.newRabbit(m_size, m_snake);
}

std::vector<Rabbit> & Model::getRabbits() {
    return m_rabbits.getData();                 // неределать на передачу фабрики
}

Way Model::getWay() {
	return m_way;
}
