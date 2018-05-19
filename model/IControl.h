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
        IControl() {};

        virtual bool isPause() const = 0;
        // метод для View, вызывается, когда клиент хочет выйти.
        virtual void quit() = 0;

        // геттер для m_quit
        virtual bool isQuit() const = 0;

        // поменять направление
        virtual void changeWay(Way _way)=0;

        virtual void nextStep()=0;
        virtual void restart()=0;


    };

}
