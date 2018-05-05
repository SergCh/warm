#include "StdAfx.h"
#include "Control.h"

#include "Model.h"
#include "View.h"

Control::Control(View& _view, Model& _model): m_view(_view), m_model(_model) {
	m_quit = false;
}

Control::~Control(void){}


Model & Control::getModel() {
	return m_model;
}

void Control::changeWay(Way _way) {
	m_model.changeWay(_way);
}

Way Control::getWay(){
	return m_model.getWay();
}

void Control::quit() {
	m_quit = true;
}

bool Control::isQuit() {
	return m_quit;
}

bool Control::move() {
	bool res = m_model.move();
	m_view.paint(m_model.getHead(), m_model.getSnake(), m_model.getRabbits());
	return res;
}

void Control::restart() {
	m_model.init();
	m_view.beforeGame();
	m_view.paint(m_model.getHead(), m_model.getSnake(), m_model.getRabbits());
}

void Control::endGame() {
	m_view.endGame(m_model.getSnake().size());
}

void Control::init() {
	restart();
}

void Control::addRabbit() {
	m_model.addRabbit();
	m_view.paint(m_model.getHead(), m_model.getSnake(), m_model.getRabbits());
}
