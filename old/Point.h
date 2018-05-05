#pragma once

#include <utility>

// TODO: ����� ����������� ���� �������


class Point: public std::pair<int, int> {

public:
	Point(int, int);
	Point();
	~Point();

	void setXY(int, int);
	int getX();
	int getY();
	
	bool between(Point& /*low*/ , Point& /*high*/);			// ����� ����� ����� (�� ������������)
	bool between(Point& /*high*/); //low = Point(-1, -1)       ���� �������������, � �� �� ������������  
	Point& operator += (const Point&);
	bool less (const Point&);
};
