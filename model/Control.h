#pragma once

#include "Way.h"

template <class T_Snake> class View;

#include "TModel.h"
#include "IControl.h"

// контроллер между View и Model

template <class T_Snake>
class Control : public IControl
{
public:
    Control(IView &, TModel<T_Snake>&);
	virtual ~Control(void);

    inline TModel<T_Snake> & getModel() const {return m_model;}

	// поменять направление
	virtual void changeWay(Way);

	// перезапуск игры
    virtual void restart();

    // следующий шаг
    virtual void nextStep();

	// инициализация 
	virtual void init();

//    Way getWay() {return m_model.getSnake().getWay();}

    std::vector<Rabbit>::iterator beginRabbit() const {return m_model.getRabbitFactory()->begin();} //зачем?
    std::vector<Rabbit>::iterator endRabbit() const {return m_model.getRabbitFactory()->end();}

protected:
	
    enum {BEGIN_STEP = 20, NEXT_STEP = 50};

    TModel<T_Snake> &m_model;
    IView &m_view;

    int steps4nextRabbit;   //steps for next rabbit
};
