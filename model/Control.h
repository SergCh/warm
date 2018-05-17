#pragma once

#include "Way.h"


#include "IControl.h"

//class IModel;
//class IView;

#include "IModel.h"
#include "IView.h"


// контроллер между View и Model

template <class T_Snake>
class Control : public IControl
{
public:
    Control(IView &, IModel&);
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

protected:
	
    enum {BEGIN_STEP = 20, NEXT_STEP = 50};

    IModel &m_model;
    IView &m_view;

    int steps4nextRabbit;   //steps for next rabbit
};
