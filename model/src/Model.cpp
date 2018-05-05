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
	m_way = Way::LEFT;
	m_length = 0;
}

void Model::changeWay(Way _way) {
	m_way = _way;
}

std::vector<Point> & Model::getSnake() {
	return m_snake;
}

bool Model::move() {
	Point newHead = m_snake[0];	// голова змея
	newHead += WAYS[m_way];		// реализован только оператор добавления

	if (!newHead.between(m_size))
		return false;

	if (std::find(m_snake.begin(), m_snake.end(), newHead) != m_snake.end())
		return false;

    m_length += m_rabbits.eat(newHead);

    m_rabbits.step();

	m_snake.insert(m_snake.begin(), newHead);

	if (m_length == 0) 
		m_snake.pop_back();
	else 
		m_length--;
	
	return true;
}


void Model::addRabbit() {
    m_rabbits.newRabbit(m_size, m_snake);
}

std::vector<Rabbit> & Model::getRabbits() {
    return m_rabbits.getData();
}

Way Model::getWay() {
	return m_way;
}
