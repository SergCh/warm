#pragma once

#include <vector>

#include "IView.h"
#include "GraphicSnake.h"
#include "RabbitFactory.h"
#include "Way.h"
#include "TGraphicView.h"

namespace Snake {

class VCView :
	public TGraphicView<VCView>
{

public:
	VCView(void);
	~VCView(void);

	virtual int getMaxPath() const {return MAX_PATH;}

    virtual void beforeGame();
    virtual void paint();
    virtual void changeScore(int _score);
	
    void nextStep();
	void changeWay(Way _way);

	int getScore() 
	{
		if (m_snake == 0) return 0;	
		return m_snake->size();
	}

	void start();
	bool isPause();

    void fillRectangle(int _x, int _y, int _w, int _h, int _c);
    void drawLine(int _x1, int _y1, int _x2, int _y2, int _c);
    void drawTextPause();
    int getSquareSize();

	void initDraw(int _squareSize)
	{
		m_squareSize = _squareSize;
		m_primitives.clear();
	}

	std::vector<int> & getPrimitives()
	{
		return m_primitives;
	}

	enum {RECTANGLE, LINE, TEXT};

private:

	int m_squareSize;
	std::vector<int> m_primitives;
};

}