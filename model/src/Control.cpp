
//#include "StdAfx.h"
#include "Control.h"

#include "Model.h"
#include "View.h"
#include "RabbitFactory.h"
#include "Rabbit.h"

Control::Control(View& _view, Model& _model):  m_model(_model) , m_view(_view) {
	m_quit = false;
    m_pause = true;
    s4nr = BEGIN_STEP;
}

Control::~Control(void){}

void Control::changeWay ( Way way) {
	m_model.changeWay(way);
}

//void Control::quit() {
//	m_quit = true;
//}

unsigned int Control::getCountRubbits() {
    return m_model.getRabbitFactory()->size();
}

Rabbit * Control::getRabbit(unsigned int i) {
    return m_model.getRabbitFactory()->at(i);
}

std::vector<Rabbit>::iterator Control::beginRabbit() {
    return m_model.getRabbitFactory()->begin();
}

std::vector<Rabbit>::iterator Control::endRabbit() {
    return m_model.getRabbitFactory()->end();
}

void Control::restart() {
	m_model.init();
	m_view.beforeGame();
    m_pause = false;
    s4nr = BEGIN_STEP;
    m_view.changeScore(m_model.getSnake().size());
}

void Control::nextStep() {
    Model::State state = Model::GOOD;
    if (!m_pause)  {
        state = m_model.move();
        if (state == Model::DEAD) {
            m_pause = true;
        } else {
            if (--s4nr<=0) {
                s4nr = NEXT_STEP;
                m_model.addRabbit();
            }
        }
    }
    if (state == Model::GOOD_CHANGED)
        m_view.changeScore(m_model.getSnake().size());
    m_view.paint();
}

void Control::init() {
    m_view.setControl(this);
    m_view.setSnake(&m_model.getSnake());
//    m_view.setRabbits(&m_model.getRabbits());
    m_view.setRabbitFactory((RabbitFactory*)m_model.getRabbitFactory());
}
