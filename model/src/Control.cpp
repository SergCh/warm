
//#include "StdAfx.h"
#include "Control.h"

#include "Model.h"
#include "View.h"

Control::Control(View& _view, Model& _model):  m_model(_model) , m_view(_view) {
	m_quit = false;
    m_pause = true;
    s4nr = BEGIN_STEP;
}

Control::~Control(void){}

void Control::changeWay ( Way way) {
	m_model.changeWay(way);
}

//Way Control::getWay(){
//	return m_model.getWay();
//}

void Control::quit() {
	m_quit = true;
}

bool Control::move() {
	bool res = m_model.move();
//	m_view.paint();
	return res;
}

void Control::restart() {
	m_model.init();
	m_view.beforeGame();
    m_pause = false;
    s4nr = BEGIN_STEP;
}

void Control::nextStep() {
    if (!m_pause)  {
        bool res=move();
        if (!res) {
            m_pause = true;
        } else {
            if (--s4nr<=0) {
                s4nr = NEXT_STEP;
                addRabbit();
            }
        }
    }
    m_view.paint();
}

//void Control::endGame() {
//	m_view.endGame(m_model.getSnake().size());
//}

void Control::init() {
    m_view.setControl(this);
    m_view.setSnake(&m_model.getSnake());
    m_view.setRabbits(&m_model.getRabbits());
}

void Control::addRabbit() {
	m_model.addRabbit();
//	m_view.paint();
}
