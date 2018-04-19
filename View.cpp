
#include "StdAfx.h"

#include <curses.h>
#include <panel.h>
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
	::curs_set(0);
}

View::~View(void) {
	::endwin();
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

void View::paint(Point& _head, std::vector<Point>& _snake, std::vector<Point>& _rabbits) {
	Draw * field = 0;

	int hField = getHieghtField();
	int wField = getWigthField();

	if (hField<=0 || wField<=0)
		return;

	Way way = m_control->getWay();
	
	::wattrset(::stdscr, COLOR_PAIR(View::Draw::EMPTY) | A_BOLD);
	::erase();

	::wattrset(::stdscr, COLOR_PAIR(View::Color::FRAME) | A_BOLD);
	::box(::stdscr, 0, 0);
	::mvprintw(m_hieght-1, 1, " For exit press: 'Q'. Snake's length=%d ", _snake.size());

	for (Point pFrom = _head; pFrom.between(Point(wField, hField)); pFrom += WAYS[way]) 
		drawDraw(pFrom, View::Draw::POINT);

	for (std::vector<Point>::iterator iter=_snake.begin(); iter != _snake.end(); iter++) {
		int i = iter - _snake.begin();
		drawDraw(*iter, i%5 == 3 ? View::Draw::BODY2 : View::Draw::BODY);
	}
		
	drawDraw(_head, View::Draw::HEAD);

	for (std::vector<Point>::iterator iter=_rabbits.begin(); iter != _rabbits.end(); iter++) 
		drawDraw(*iter, View::Draw::RABBIT);

	::move(m_hieght-1, m_wigth-1);
	::refresh();
}

void View::drawDraw(Point & _point, Draw _draw) {
	char c = ' ';
	chtype bold = A_NORMAL;
	switch (_draw) {
		case View::Draw::RABBIT: c = '&'; bold = A_BOLD; break;
		case View::Draw::BODY:   c = '*'; bold = A_BOLD; break;
		case View::Draw::BODY2:  c = '*'; bold = A_BOLD; break;
		case View::Draw::HEAD:   c = '%'; bold = A_BOLD; break;
		case View::Draw::POINT:  c = '.'; bold = A_BOLD; break;
	}
	::attrset(COLOR_PAIR(_draw) | bold);
	::mvaddch(_point.getY()+1, _point.getX()+1, c);
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
			m_control->changeWay(Way::DOWN);
			return;
		case KEY_UP:
			m_control->changeWay(Way::UP);
			return;
		case KEY_LEFT:
			m_control->changeWay(Way::LEFT);
			return;
		case KEY_RIGHT:
			m_control->changeWay(Way::RIGHT);
			return;
		case 'Q':
		case 'q':
			m_control->quit();
			return;
	}
}

void View::initColors() {
	::init_pair(View::Draw::EMPTY,  COLOR_WHITE, COLOR_BLACK);
	::init_pair(View::Draw::HEAD,   COLOR_RED,   COLOR_BLACK);
	::init_pair(View::Draw::BODY,   COLOR_RED,   COLOR_BLACK);
	::init_pair(View::Draw::BODY2,  COLOR_YELLOW,COLOR_BLACK);
	::init_pair(View::Draw::RABBIT, COLOR_WHITE, COLOR_GREEN);
	::init_pair(View::Draw::POINT,  COLOR_BLUE,  COLOR_BLACK);

	::init_pair(View::Color::FRAME,   COLOR_WHITE, COLOR_MAGENTA);
	::init_pair(View::Color::DIALOG,  COLOR_WHITE, COLOR_BLUE);
}

void View::beforeGame() {
	::nodelay(::stdscr, TRUE);
	::flushinp();
}

void View::endGame(int len) {
	int dx = 40, dy = 5;
	int x = (m_wigth - dx) / 2, y = (m_hieght - dy) / 2;

	const std::string message("You result = %d");

	WINDOW *win = ::newwin(dy, dx, y, x);

	if (!win) return ;

	::wattrset(win, COLOR_PAIR(View::Color::DIALOG) | A_BOLD);
	::wbkgd(win, COLOR_PAIR(View::Color::DIALOG) | A_BOLD);
	::nodelay(win, FALSE);

	::werase(win);
	::box(win, 0, 0);
	::mvwprintw(win, dy-1, 1, " 'Q' - exit, space - restart ");

	::mvwprintw(win, (dy-1)/2, (dx - message.length()+1)/2 , message.c_str(), len);
	::wrefresh(win);

	do {
		int ch = wgetch(win);
		switch (ch) {
			case 'Q':
			case 'q':
				m_control->quit();
			case ' ':
				::delwin(win);
				return;
		}
	} while (true);
}
