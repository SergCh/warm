
#include "StdAfx.h"

#include <curses.h>
#include <stdlib.h>

#include "View.h"
#include "Point.h"
#include "Control.h"
#include "Model.h"

View::View(void) {
	m_control = 0;

	::initscr();
	::keypad(::stdscr, TRUE);
	::nodelay(::stdscr, TRUE);
	::cbreak();
	::noecho();
    if (has_colors())
        start_color();
	m_hieght = getSystemHieght();
	m_wigth = getSystemWigth();
	initColors();
}

View::~View(void) {
}

int View::getHieghtField() {
	return m_hieght-2;
}

int View::getWigthField() {
	return m_wigth-2;
}

void View::setHieght(int _hieght) {
	m_hieght = _hieght;
}

void View::setWigth(int _wigth) {
	m_wigth = _wigth;
}

void View::setControl(Control* _control) {
	m_control = _control;
}

void View::paint(Point& head, std::vector<Point>& piton, std::vector<Point>& rabbits) {
	Draw * field = 0;

	int hField = getHieghtField();
	int wField = getWigthField();

	if (hField<=0 || wField<=0)
		return;

	if (!(field = new Draw[hField*wField]))
		return;

	for (int i = 0, size = hField*wField; i<size; i++)
		field[i] = EMPTY;

	Way way = m_control->getWay();

	Point pFrom, pTo, pInc;
	switch (way) {
	case UP:	pFrom = Point(head.getX(), 0);
				pTo   = Point(head.getX()+1, head.getY());
				pInc  = Point(0, 1);
				break;
	case DOWN:  pFrom = Point(head.getX(), head.getY()+1);
		        pTo   = Point(head.getX()+1, hField);
				pInc  = Point(0, 1);
				break;
	case LEFT:  pFrom = Point(0, head.getY());
				pTo   = Point(head.getX(), head.getY()+1);
				pInc  = Point(1, 0);
				break;
	case RIGHT: pFrom = Point(head.getX()+1, head.getY());
				pTo   = Point(wField, head.getY()+1);
				pInc  = Point(1, 0);
				break;
	}

	for (; pFrom.less(pTo) ; pFrom += pInc) 
		putDraw(field, pFrom, POINT);

	for (std::vector<Point>::iterator iter=piton.begin(); iter != piton.end(); iter++) 
		putDraw(field, *iter, BODY);

	putDraw(field, head, HEAD);

	for (std::vector<Point>::iterator iter=rabbits.begin(); iter != rabbits.end(); iter++) 
		putDraw(field, *iter, RUBBIT);

	Draw * iterField = field;
	for (int y=0; y<hField; y++)
		for (int x=0; x<wField; x++, iterField++) 
			drawDraw(x+1, y+1, *iterField);

	delete []field;

	paintFrame(piton.size());

	::move(::LINES - 1, ::COLS - 1);
	::refresh();
}

void View::putDraw(Draw* _field, Point& _point, Draw _draw) {
	if (!_point.between(Point(-1, -1), Point(getWigthField(), getHieghtField())))
		return;
	_field[_point.getY() * getWigthField() + _point.getX()] = _draw;
}

void View::paintFrame(int _length) {
	int systemHieght = getSystemHieght();
	int systemWigth = getSystemWigth();

	for (int x=1; x < systemWigth-1; x++) {
		drawFrame(x, 0, HORIZONTAL);
		drawFrame(x, systemHieght-1, HORIZONTAL);
	}

	for (int y=1; y < systemHieght-1; y++) {
		drawFrame(0, y, VERTICAL);
		drawFrame(systemWigth-1, y, VERTICAL);
	}

	drawFrame(0, 0, LEFTUP);
	drawFrame(systemWigth-1, 0, RIGTHUP);
	drawFrame(0, systemHieght-1, LEFTDOWN);
	drawFrame(systemWigth-1, systemHieght-1, RIGTHDOWN);

	::attrset(COLOR_PAIR(FRAME) | A_BOLD);

	char buf[33];
	std::string s = " For exit press: 'Q'. Snake's length= "; 
	s += std::string(::itoa(_length, buf, 10));
	s += std::string(" ");
	::mvaddstr(systemHieght-1, 1, s.c_str());
}

void View::drawDraw(int x, int y, Draw draw) {
	char c = ' ';
	chtype bold = A_NORMAL;
	switch (draw) {
		case RUBBIT: c = '@'; bold = A_BOLD; break;
		case BODY:   c = '*'; bold = A_BOLD; break;
		case HEAD:   c = '%'; bold = A_BOLD; break;
		case POINT:  c = '.'; break;
	}
	::attrset(COLOR_PAIR(draw) | bold);
	::mvaddch(y, x, c);
}

void View::drawFrame(int x, int y, View::Frame frame) {
	unsigned long c = ' ';
	switch (frame) {
		case VERTICAL:   c = ACS_VLINE; break;
		case HORIZONTAL: c = ACS_HLINE; break;
		case LEFTUP:     c = ACS_ULCORNER; break;
		case RIGTHUP:    c = ACS_URCORNER; break;
		case LEFTDOWN:   c = ACS_LLCORNER; break;
		case RIGTHDOWN:  c = ACS_LRCORNER; break;
	}
	::attrset(COLOR_PAIR(FRAME) | A_BOLD);
	::mvaddch(y, x, c);
}



int View::getSystemHieght() {
	return ::LINES;
}

int View::getSystemWigth() {
	return ::COLS;
}

void View::getCommands() {
	int ch = getch();
	::napms(100);
	if (ch == ERR) return;
	switch (ch) {
		case KEY_DOWN:
			m_control->changeWay(DOWN);
			return;
		case KEY_UP:
			m_control->changeWay(UP);
			return;
		case KEY_LEFT:
			m_control->changeWay(LEFT);
			return;
		case KEY_RIGHT:
			m_control->changeWay(RIGHT);
			return;
		case 'Q':
		case 'q':
			m_control->quit();
			return;
	}
}

void View::initColors() {
	// frame
	::init_pair(EMPTY,  COLOR_WHITE, COLOR_BLACK);
	::init_pair(HEAD,   COLOR_RED,   COLOR_YELLOW);
	::init_pair(BODY,   COLOR_RED,   COLOR_YELLOW);
	::init_pair(RUBBIT, COLOR_BLUE,  COLOR_GREEN);
	::init_pair(POINT,  COLOR_BLUE,  COLOR_BLACK);
	::init_pair(FRAME,  COLOR_WHITE, COLOR_MAGENTA);
}
