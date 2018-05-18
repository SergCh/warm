#pragma once

/**
 * @file IControl.h
 * @brief %{Cpp:License:ClassName}
 * @author Чугайнов С.В.
 * @date 17.05.2018
 *
 *
 */

#include "Way.h"

namespace SNAKE_MODEL {

    class Rabbits;

    class IControl
    {
    public:
        IControl() {
            m_quit = false;
            m_pause = true;
        }

        inline bool isPause() const {return m_pause;}
        // метод для View, вызывается, когда клиент хочет выйти.
        inline void quit() {m_quit = true;}

        // геттер для m_quit
        inline bool isQuit() const {return m_quit;}

        // поменять направление
        virtual void changeWay(Way _way)=0;

        virtual void nextStep()=0;
        virtual void restart()=0;

    protected:
        // флаг выхода
        bool m_quit;
        // флаг паузы
        bool m_pause;


    };

}
