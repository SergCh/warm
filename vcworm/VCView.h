#pragma once

#include "IView.h"
#include "GraphicSnake.h"
#include "RabbitFactory.h"
#include "Way.h"

namespace Snake {

class VCView :
	public IView
{

public:
	VCView(void);
	~VCView(void);

    virtual int getHieghtField();
    virtual int getWidthField();
    virtual void setSnake(ISnake * _snake);
	virtual int getMaxPath() const {return MAX_PATH;}

    virtual void beforeGame();
    virtual void paint();
    virtual void changeScore(int _score);
	
    void nextStep();
	void setHieght(int);
	void setWigth(int);
	void changeWay(Way _way);

	GraphicSnake * getSnake() {return m_snake;}
	RabbitFactory * getRabbitFactory() {return m_rabbitFactory;}

	void start();
	bool isPause();

private:
	enum { BOARD_WIDTH = 50, BOARD_HEIGHT = 50, MAX_PATH = 10 };
    GraphicSnake * m_snake;

};

}