#include "VCView.h"
#include "IControl.h"

using namespace Snake;

VCView::VCView(void)
{
	m_snake = 0;
}

VCView::~VCView(void)
{
}


void VCView::start()
{
	if (m_control == 0)
		return;
	m_control->restart();
}

bool VCView::isPause()
{
	if (m_control == 0) 
		return true;
	return m_control->isPause();
}


void VCView::beforeGame()
{
	if (m_snake == 0) 
		return;
	m_snake->setMaxPath(MAX_PATH);
}

void VCView::paint()
{
}

void VCView::changeScore(int _score)
{
}

void VCView::changeWay(Way _way) 
{
	if (m_control == 0) 
		return;
	m_control->changeWay(_way);
}


void VCView::nextStep()
{
	if (m_control == 0) 
		return;
	return m_control->nextStep();
}

//void VCView::setHieght(int){}

//void VCView::setWigth(int){}


void VCView::fillRectangle(int _x, int _y, int _w, int _h, int _c)
{
	m_primitives.push_back(RECTANGLE);
	m_primitives.push_back(_x);
	m_primitives.push_back(_y);
	m_primitives.push_back(_w);
	m_primitives.push_back(_h);
	m_primitives.push_back(_c);
}

void VCView::drawLine(int _x1, int _y1, int _x2, int _y2, int _c)
{
	m_primitives.push_back(LINE);
	m_primitives.push_back(_x1);
	m_primitives.push_back(_y1);
	m_primitives.push_back(_x2);
	m_primitives.push_back(_y2);
	m_primitives.push_back(_c);
}

void VCView::drawTextPause()
{
	m_primitives.push_back(TEXT);
}

int VCView::getSquareSize()
{
	return m_squareSize;
}
