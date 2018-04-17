#pragma once

#include <queue>

#include "Point.h"
#include "ways.h"

class Model {
private:
	static const int ADD_LENGTH = 5;

public:
	Model(int /*w*/, int /*h*/);
	~Model(void);
	
	void init();

	std::vector<Point> & getSnake();
	Point &getHead();

	void changeWay(Way);
	Way getWay();
	void addRabbit();
	std::vector<Point> & getRabbits();

	bool move();

private:

	bool check();

	std::vector<Point> m_snake;
	std::vector<Point> m_rabbits;

	int m_hieght;
	int m_wigth;

	Way m_way;
	int m_length;

};
