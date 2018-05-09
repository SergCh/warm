#pragma once

#include "Way.h"

//class Model;
class View;

#include "Model.h"

// контроллер между View и Model

class Control
{
public:
	Control(View&, Model&);
	virtual ~Control(void);

    Model & getModel() const {return m_model;}

	// поменять направление
	virtual void changeWay(Way);

	// получить текущее направление
    Way getWay() const {return m_model.getWay();}

    bool isPause() const {return m_pause;}

	// метод для View, срабатывает, когда клиент хочет выйти.
	void quit();

	// геттер для m_quit
    bool isQuit() const {return m_quit;}

	// делаем один шаг
	virtual bool move();

	// перезапуск игры
	virtual void restart();

    // следующий шаг
    virtual void nextStep();

	// инициализация 
	virtual void init();

private:
	
    const int BEGIN_STEP = 20;
    const int NEXT_STEP = 50;

	Model &m_model;
	View &m_view;

	// флаг выхода 
	bool m_quit;
    // флаг паузы
    bool m_pause;
    // кол-во шагов до нового кролика
    int s4nr;   //steps for next rabbit
};
