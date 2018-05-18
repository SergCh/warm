#include "VCView.h"
#include "IControl.h"

using namespace SNAKE_MODEL;

VCView::VCView(void)
{
	m_snake = 0;
}

VCView::~VCView(void)
{
}

int VCView::getHieghtField() 
{
	return BOARD_HEIGHT;
}
int VCView::getWidthField()
{
	return BOARD_WIDTH;
}

void VCView::setSnake(ISnake * _snake) 
{
    m_snake = static_cast<GraphicSnake*> (_snake);
}

void VCView::start()
{
	if (m_control != 0) {
		m_control->restart();
	}
}

bool VCView::isPause()
{
	if (m_control == 0) 
		return true;
	return m_control->isPause();
}


void VCView::beforeGame()
{
}

void VCView::paint()
{
}

void VCView::changeScore(int _score)
{
}

void VCView::nextStep()
{
}

void VCView::setHieght(int){}

void VCView::setWigth(int){}