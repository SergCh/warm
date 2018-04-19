#pragma once

#include <utility>

// TODO: Нужен рефакторинг имен методов


class Point: public std::pair<int, int> {

public:
	Point(int, int);
	Point();
	~Point();

	void setXY(int, int);
	int getX();
	int getY();
	
	bool between(Point& /*low*/ , Point& /*high*/);			// Точка между двумя (не включительно)
	bool between(Point& /*high*/); //low = Point(-1, -1)       можт переименовать, а то не соотвествует  
	Point& operator += (const Point&);
	bool less (const Point&);
};
