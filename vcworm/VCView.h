#pragma once

#include "IView.h"
#include "GraphicSnake.h"
#include "RabbitFactory.h"

namespace SNAKE_MODEL {

class VCView :
	public IView
{

public:
	VCView(void);
	~VCView(void);

    virtual int getHieghtField();
    virtual int getWidthField();
    virtual void setSnake(ISnake * _snake);

    virtual void beforeGame();
    virtual void paint();
    virtual void changeScore(int _score);
    void nextStep();
	void setHieght(int);
	void setWigth(int);

	GraphicSnake * getSnake() {return m_snake;}
	RabbitFactory * getRabbitFactory() {return m_rabbitFactory;}

	void start();
	bool isPause();

private:
	enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50, MAX_PATH = 10 };
    GraphicSnake * m_snake;

};

}