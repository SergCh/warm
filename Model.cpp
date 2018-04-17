#include "StdAfx.h"
#include <algorithm>

#include "Model.h"

Model::Model(int _wigth, int _hieght) {
	m_hieght = _hieght;
	m_wigth = _wigth;
}

Model::~Model(void) {
}

void Model::init() {
	m_snake.clear();
	m_rabbits.clear();
	int x = m_wigth / 2, y = m_hieght / 2;
	m_snake.push_back(Point(x,y));
	m_snake.push_back(Point(x+1,y));
	m_way = LEFT;
	m_length = 0;
}

void Model::changeWay(Way _way) {
	m_way = _way;
}

std::vector<Point> & Model::getSnake() {
	return m_snake;
}

bool Model::move() {
	if (!check()) 
		return false;

	if (m_length == 0) 
		m_snake.pop_back();
	else 
		m_length--;
	
	return true;
}

Point &Model::getHead(){
	return m_snake.at(0);
}

bool Model::check() {
	Point ways[4];
	ways[UP]    = Point( 0,-1);
	ways[DOWN]  = Point( 0, 1);
	ways[LEFT]  = Point(-1, 0);
	ways[RIGHT] = Point( 1, 0);

	Point head = getHead();
	Point newHead = (ways[m_way] += head);

	if (!newHead.between(Point(-1, -1), Point(m_wigth, m_hieght)))
		return false;
	
	if (std::find(m_snake.begin(), m_snake.end(), newHead) != m_snake.end())
		return false;
	
	std::vector<Point>::iterator iter;
	if ((iter=std::find(m_rabbits.begin(), m_rabbits.end(), newHead)) != m_rabbits.end()) {
		m_rabbits.erase(iter);
		m_length += ADD_LENGTH;
	}
	m_snake.insert(m_snake.begin(), newHead);
	return true;
}


void Model::addRabbit() {
	do {
		Point rabbit(rand()%m_wigth, rand()%m_hieght);

		if (std::find(m_snake.begin(), m_snake.end(), rabbit) != m_snake.end())
			continue;
		if (std::find(m_rabbits.begin(), m_rabbits.end(), rabbit) != m_rabbits.end())
			continue;

		m_rabbits.push_back(rabbit);
		break;

	} while(true);
}

std::vector<Point> & Model::getRabbits() {
	return m_rabbits;
}

Way Model::getWay() {
	return m_way;
}
