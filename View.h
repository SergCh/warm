#pragma once

#include <vector>

#include "Point.h"

class Control;


class View
{
public:
	View(void);
	~View(void);

	void setControl(Control*);

	void paint(Point& /*head*/, std::vector<Point>& /*piton*/, std::vector<Point>& /*rabbits*/);
	void paintFrame(int);

	int getHieghtField();
	int getWigthField();

	void setHieght(int);
	void setWigth(int);

	int getSystemHieght();
	int getSystemWigth();

	void getCommands();

private:
	typedef enum {EMPTY, HEAD, BODY, RUBBIT, POINT, FRAME} Draw;
	typedef enum {VERTICAL, HORIZONTAL, LEFTUP, RIGTHUP, LEFTDOWN, RIGTHDOWN} Frame;

	void putDraw(Draw*, Point&, Draw);

	void drawDraw(int /*x*/, int /*y*/, Draw);
	void drawFrame(int /*x*/, int /*y*/, Frame);

	void initColors();

	Control *m_control;

	int m_hieght;
	int m_wigth;

};
