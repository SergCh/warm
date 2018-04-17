#include "StdAfx.h"
#include "Point.h"

Point::Point(int x, int y):pair<int,int>(x,y){}

Point::Point():pair<int,int>(0,0){}

Point::~Point(void){}

void Point::setXY(int _x, int _y) {
	first = _x;
	second = _y;
}

int Point::getX() {
	return first;
}

int Point::getY() {
	return second;
}

bool Point::between(Point& _low, Point& _high) {
	return _low.less(*this) && less(_high);
}


Point& Point::operator += (const Point& p) {
	first += p.first;
	second += p.second;
	return *this;
}

bool Point::less (const Point& p) {
	return first<p.first && second<p.second;
}

