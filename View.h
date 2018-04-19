#pragma once

/*

	Тут весь вывод на экран и получения реакции от игрока

*/

#include <vector>

#include "Point.h"

class Control;


class View
{
public:
	View(void);
	~View(void);

	void setControl(Control*);

	void paint(Point& /*head*/, std::vector<Point>& /*snake*/, std::vector<Point>& /*rabbits*/);
	
	int getHieghtField();
	int getWigthField();

	void setHieght(int);
	void setWigth(int);

	int getSystemHieght();
	int getSystemWigth();

	void getCommands();

	void beforeGame();
	void endGame(int);

private:
	typedef enum {EMPTY = 1, HEAD, BODY, BODY2, RABBIT, POINT} Draw;	//TODO: не удачное название Draw
	typedef enum {FRAME = Draw::POINT+1, DIALOG} Color;

	void drawDraw(Point &, Draw);

	void initColors();

	Control *m_control;

	int m_hieght;
	int m_wigth;
};
