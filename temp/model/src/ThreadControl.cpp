
#include "ThreadControl.h"

ThreadControl::ThreadControl(View& _view, Model& _model):Control(_view, _model), m_mutexModel() {
}

ThreadControl::~ThreadControl() {}


void ThreadControl::changeWay(Way way) {
	m_mutexModel.lock();
	Control::changeWay(way);
	m_mutexModel.unlock();
}

void ThreadControl::addRabbit() {
	m_mutexModel.lock();
	Control::addRabbit();
	m_mutexModel.unlock();
}


bool ThreadControl::move() {
	m_mutexModel.lock();
	bool res=Control::move();
	m_mutexModel.unlock();
	return res;
}

void ThreadControl::restart() {
	m_mutexModel.lock();
	Control::restart();
	m_mutexModel.unlock();
}


