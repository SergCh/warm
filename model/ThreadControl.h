#pragma once

#include <mutex>

#include "Control.h"
#include "Way.h"

class Model;
class View;

// контроллер с мьютексом между View и Model

class ThreadControl : public Control
{
public:
	ThreadControl(View&, Model&);
	virtual ~ThreadControl(void);

	// поменять направление
	virtual void changeWay(Way);

	// делаем один шаг
	virtual bool move();

	// перезапуск игры
	virtual void restart();

	virtual void addRabbit();

private:

	// мьютекс для модели
	std::mutex m_mutexModel;

};
