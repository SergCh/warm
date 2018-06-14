#pragma once

#include "Way.h"

#include "IControl.h"

#include "IModel.h"
#include "IView.h"

namespace Snake {

    // контроллер между View и Model

    class Control : public IControl
    {
    public:
        Control(IView &, IModel&);
        virtual ~Control(void);

        IModel & getModel() const {return m_model;}

        // поменять направление
        virtual void changeWay(Way);

        // перезапуск игры
        virtual void restart();

        // следующий шаг
        virtual void nextStep();

        // инициализация
        virtual void init();

        bool isPause() const {return m_pause;}
        // метод для View, вызывается, когда клиент хочет выйти.
        void quit() {m_quit = true;}

        // геттер для m_quit
        bool isQuit() const {return m_quit;}


    protected:

        enum {BEGIN_STEP = 20, NEXT_STEP = 50};

        IModel &m_model;
        IView &m_view;

        int steps4nextRabbit;   //steps for next rabbit

        // флаг выхода
        bool m_quit;
        // флаг паузы
        bool m_pause;

    };

}
