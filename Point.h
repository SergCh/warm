#pragma once

#include <utility>


class Point: public std::pair<int, int> {

public:
	Point(int, int);
	Point();
	~Point();

	void setXY(int, int);
	int getX();
	int getY();

	
	bool between(Point& /*low*/, Point& /*high*/);
	Point& operator += (const Point&);
	bool less (const Point&);
};
