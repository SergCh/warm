
//#include "StdAfx.h"

#include <string>

#include <ncurses.h>
#include <stdlib.h>

#include "CursesVersion.h"

#include "CursesView.h"
#include "Point.h"
#include "Control.h"
#include "TModel.h"
#include "Rabbit.h"
#include "RabbitFactory.h"

CursesView::CursesView() : View() {
	initscr();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	cbreak();
	noecho();
    if (has_colors()) {
        start_color();
    }
	m_hieght = getSystemHieght();
    m_width = getSystemWigth();
	initColors();
	curs_set(0);
    m_score=0;
}

CursesView::~CursesView() {
	endwin();
}

int CursesView::getHieghtField() {
	return m_hieght-2;
}

int CursesView::getWidthField() {
    return (m_width-2) / 2;
}

void CursesView::setHieght(int _hieght) {
	m_hieght = _hieght;
}

void CursesView::setWigth(int _wigth) {
    m_width = _wigth;
}

void CursesView::drawDraw(Point & _point, Draw _draw) {
    char c1 = ' ';
    char c2 = ' ';
	chtype bold = A_NORMAL;
	switch (_draw) {
        case Draw::RABBIT: c1 = '>'; c2 = '@'; bold = A_BOLD; break;
        case Draw::BODY:   c1 = '('; c2 = ')'; bold = A_BOLD; break;
        case Draw::BODY2:  c1 = '('; c2 = ')'; bold = A_BOLD; break;
        case Draw::HEAD:   c1 = 'o'; c2 = 'O'; bold = A_BOLD; break;
        case Draw::POINT:  c1 = '.'; c2 = ' '; bold = A_BOLD; break;
        case Draw::EMPTY:  break;  //добавил, иначе KDevelop ругается
	}
	
	attrset(COLOR_PAIR(_draw) | bold);
    mvaddch(_point.getY()+1, (_point.getX()*2)+1, c1);
    mvaddch(_point.getY()+1, (_point.getX()*2)+2, c2);
}

int CursesView::getSystemHieght() {
	return LINES;
}

int CursesView::getSystemWigth() {
	return COLS;
}

void CursesView::getCommands() {
	int ch = getch();
	napms(100);
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

void CursesView::initColors() {
	init_pair(Draw::EMPTY,  COLOR_WHITE, COLOR_BLACK);
	init_pair(Draw::HEAD,   COLOR_RED,   COLOR_BLACK);
	init_pair(Draw::BODY,   COLOR_RED,   COLOR_BLACK);
	init_pair(Draw::BODY2,  COLOR_YELLOW,COLOR_BLACK);
	init_pair(Draw::RABBIT, COLOR_WHITE, COLOR_GREEN);
	init_pair(Draw::POINT,  COLOR_BLUE,  COLOR_BLACK);

	init_pair(Color::FRAME,   COLOR_WHITE, COLOR_MAGENTA);
	init_pair(Color::DIALOG,  COLOR_WHITE, COLOR_BLUE);
}

void CursesView::beforeGame() {
	nodelay(stdscr, TRUE);
	flushinp();
}

void CursesView::endGame(int score) {
	int dx = 40, dy = 5;
    int x = (m_width - dx) / 2, y = (m_hieght - dy) / 2;

    const std::string message(score?"Your score = %d":"Game time");

	WINDOW *win = newwin(dy, dx, y, x);

	if (!win) return ;

	wattrset(win, COLOR_PAIR(CursesView::Color::DIALOG) | A_BOLD);
	wbkgd(win, COLOR_PAIR(CursesView::Color::DIALOG) | A_BOLD);
	nodelay(win, FALSE);

	werase(win);
	box(win, 0, 0);
	mvwprintw(win, dy-1, 1, " 'Q' - exit, space - restart ");

    mvwprintw(win, (dy-1)/2, (dx - message.length())/2 , message.c_str(), score);
	wrefresh(win);

	do {
		int ch = wgetch(win);
		switch (ch) {
			case 'Q':
			case 'q':
				m_control->quit();
			case ' ':
				delwin(win);
				return;
		}
	} while (true);
}


void CursesView::paint() {
    beforePaintField();
    if (m_control == 0)
        return;
    if (getHieghtField()>0 && getWidthField()>0) {
        m_way = m_control->getWay();

        if (m_snake != 0 && m_snake->size() > 0) {
            paintWay();
            paintSnake();
        }

//        if (m_rabbits != 0)
//            for (std::vector<Rabbit>::iterator iter=m_rabbits->begin(); iter != m_rabbits->end(); iter++)
        for (std::vector<Rabbit>::iterator iter=m_rf->begin(); iter != m_rf->end(); iter++)
            paintRabbit(*iter);
    }
    afterPaintField();

    if (m_control->isPause()) {
        const int score = m_snake==0? 0 : m_snake->size();
        endGame(score);
        m_control->restart();
    }
}


void CursesView::changeScore(int _score, int) { //вся прорисовка произходит в paint()
    m_score = _score;
}

void CursesView::beforePaintField() {
	wattrset(stdscr, COLOR_PAIR(Draw::EMPTY) | A_BOLD);
	erase();

	wattrset(stdscr, COLOR_PAIR(Color::FRAME) | A_BOLD);
	box(stdscr, 0, 0);
    
    mvprintw(m_hieght-1, 1, " For exit press: 'Q'. Snake's length=%d ", m_score);
    const std::string versionModel(VERSION_MODEL);
    const std::string versionView(VERSION_CURSES);
    const int len = versionModel.length() + versionView.length() + 6;
    mvprintw(0, m_width - len, "v:%s m:%s", versionView.c_str(), versionModel.c_str());
}

void CursesView::afterPaintField() {
    move(m_hieght-1, m_width-1);
	refresh();
}

void CursesView::paintWay() {
    Point pEnd = Point(getWidthField(), getHieghtField());
    Point pFrom = m_snake->at(0);
    for (; pFrom.between(pEnd); pFrom += m_way.getPoint())
		drawDraw(pFrom, Draw::POINT);
}

void CursesView::paintSnake() {
	for (std::vector<Point>::iterator iter=m_snake->begin(); iter != m_snake->end(); iter++) {
		int i = iter - m_snake->begin();
		drawDraw(*iter, i%5 == 3 ? Draw::BODY2 : Draw::BODY);
	}
	drawDraw(m_snake->at(0), Draw::HEAD);
}

void CursesView::paintRabbit(Rabbit & rabbit) {
    Point point = rabbit.getPoint();
    drawDraw(point, Draw::RABBIT);
}
