
#include "Point.h"

using namespace SNAKE_MODEL;

Point::Point(int _x, int _y):pair<int,int>(_x, _y){}

Point::Point():pair<int,int>(0, 0){}

void Point::setXY(int _x, int _y) {
	first = _x;
	second = _y;
}

bool Point::between(Point& _low, Point& _high) {
	return _low.less(*this) && less(_high);
}

bool Point::between(Point& _high) {
    Point low = Point(-1, -1);
	return between(low, _high);
}

Point& Point::operator += (const Point& _point) {
    first += _point.first;
    second += _point.second;
	return *this;
}

bool Point::less (const Point& _point) {
    return first<_point.first && second<_point.second;
}

