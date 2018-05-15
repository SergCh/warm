#pragma once

#include "Way.h"

class View;

#include "TModel.h"
#include "Config.h"

// контроллер между View и Model

class Control
{
public:
    Control(View&, Model&);
	virtual ~Control(void);

    inline Model & getModel() const {return m_model;}

	// поменять направление
	virtual void changeWay(Way);

    inline bool isPause() const {return m_pause;}

    // метод для View, вызывается, когда клиент хочет выйти.
    inline void quit() {m_quit = true;}

	// геттер для m_quit
    inline bool isQuit() const {return m_quit;}

	// перезапуск игры
	virtual void restart();

    // следующий шаг
    virtual void nextStep();

	// инициализация 
	virtual void init();

    unsigned int getCountRubbits() const {return m_model.getRabbitFactory()->size();}

    std::vector<Rabbit>::iterator beginRabbit() const {return m_model.getRabbitFactory()->begin();}
    std::vector<Rabbit>::iterator endRabbit() const {return m_model.getRabbitFactory()->end();}

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
    int steps4nextRabbit;   //steps for next rabbit
};
